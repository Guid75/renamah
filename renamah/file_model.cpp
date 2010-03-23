/*
 * Renamah
 * Copyright (C) 2009 Guillaume Denry <guillaume.denry@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QFileInfo>
#include <QPair>
#include <QIcon>
#include <QMimeData>
#include <QDateTime>

#include "filter_model.h"

#include "file_model.h"

FileModel *FileModel::_instance = 0;

FileModel &FileModel::instance()
{
    if (!_instance)
        _instance = new FileModel;

    return *_instance;
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    return _originals.count();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    QString original = _originals[index.row()];
    QFileInfo originalFileInfo(original);
    QString renamed;
    bool manual = false;

    if (_manualMapping.find(original) != _manualMapping.end()) {
        manual = true;
        renamed = _manualMapping[original];
    }
    else if (_renamedMapping.find(original) != _renamedMapping.end())
        renamed = _renamedMapping[original];
    else
    {
        renamed = FilterModel::instance().apply(original, index.row());
        const_cast<QMap<QString,QString> &>(_renamedMapping)[original] = renamed;
    }

    switch (role)
    {
    case Qt::DisplayRole:
        switch (index.column())
        {
        case 0: return originalFileInfo.fileName();
        case 1: return QFileInfo(renamed).fileName();
        default:;
        }
        break;
	case Qt::ForegroundRole:
        switch (index.column())
        {
        case 1:
            if (manual)
                return Qt::red;
            else if (renamed != original)
                return Qt::blue;
            break;
        default:;
        }
        break;
	case Qt::DecorationRole:
        if (index.column() == 1) {
            if (manual)
                return QIcon(":/images/hand.png");
            else if (renamed != original)
                return QIcon(":/images/automatic.png");
            else
                return QIcon(":/images/blank.png");
        }
	default:;
	}

    return QVariant();
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
        switch (section)
        {
        case 0: return tr("Original");
        case 1: return tr("Renamed");
        default:;
        }
    return QVariant();
}

void FileModel::addFile(const QString &filePath)
{
    if (_originals.indexOf(filePath) >= 0)
        return;

    beginInsertRows(QModelIndex(), _originals.count(), _originals.count());
    _originals << filePath;
    endInsertRows();
    invalidate();
}

bool FileModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > rowCount() - 1 ||
        row + count < 0 || row + count > rowCount())
        return false;

    beginRemoveRows(parent, row, row + count - 1);

    while (count)
    {
        QString fileName = _originals[row];
        _originals.removeAt(row);
        _renamedMapping.remove(fileName);
        _manualMapping.remove(fileName);

        count--;
    }

    endRemoveRows();
    invalidate();
}

void FileModel::invalidate() {
    _renamedMapping.clear();

    if (rowCount())
        emit dataChanged(index(0, 1), index(rowCount() - 1, 1));
}

QString FileModel::originalFileName(const QModelIndex &index) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return "";

    return _originals[index.row()];
}

QString FileModel::renamedFileName(const QModelIndex &index) const {
    if (index.row() < 0 || index.row() >= rowCount())
        return "";

    QString original = _originals[index.row()];
    if (_manualMapping.find(original) != _manualMapping.end())
        return _manualMapping[original];
    else
        return FilterModel::instance().apply(original, index.row());
}

void FileModel::setManualRenaming(const QModelIndex &index, const QString &renamedFileName) {
    QString original = originalFileName(index);
    if (original == "")
        return;

    _manualMapping[original] = renamedFileName;
    _renamedMapping.remove(original);

    emit dataChanged(this->index(index.row(), 0), this->index(index.row(), columnCount() - 1));
}

void FileModel::removeManualRenaming(const QModelIndex &index) {
    QString original = originalFileName(index);
    if (original == "")
        return;

    _manualMapping.remove(original);
    _renamedMapping.remove(original);

    emit dataChanged(this->index(index.row(), 0), this->index(index.row(), columnCount() - 1));
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | flags;
    else
        return Qt::ItemIsDropEnabled | flags;
}

Qt::DropActions FileModel::supportedDropActions() const {
    return Qt::MoveAction;
}

#define MIMETYPE QLatin1String("file-rows")

QStringList FileModel::mimeTypes() const {
    QStringList types;
    types << MIMETYPE;
    return types;
}

QMimeData *FileModel::mimeData(const QModelIndexList &indexes) const {
    QMimeData *mimeData = new QMimeData;
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    QList<int> rowsToMove;
    foreach (QModelIndex index, indexes) {
        if (index.isValid()) {
            if (rowsToMove.indexOf(index.row()) < 0) {
                rowsToMove << index.row();
                stream << index.row();
            }
        }
    }

    mimeData->setData(MIMETYPE, encodedData);
    return mimeData;
}

bool FileModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) {
    if (action == Qt::IgnoreAction)
        return false;

    _dropRows.clear();

    // Get the rows to move
    QList<int> rowsToMove;
    QByteArray inData = data->data(MIMETYPE);
    QDataStream stream(inData);
    while (!stream.atEnd()) {
        int r;
        stream >> r;
        rowsToMove << r;
    }
    qSort(rowsToMove);

    QStringList filesToMove;
    int insertionIndex = row;
    int parentInsertionIndex = parent.isValid() ? parent.row() : -1;
    foreach (int rowIndex, rowsToMove) {
        if (rowIndex < row)
            insertionIndex--;
        if (rowIndex < parent.row()) {
            parentInsertionIndex--;
        }
        filesToMove << _originals[rowIndex];
    }

    for (int i = 0; i < rowsToMove.count(); ++i) {
        _originals.removeAt(rowsToMove[i] - i);
    }

    if (insertionIndex != -1) {
        if (insertionIndex >= rowCount()) {
            foreach (const QString &fileName, filesToMove) {
                _dropRows << _originals.count();
                _originals << fileName;
            }
        } else {
            int i = 0;
            foreach (const QString &fileName, filesToMove) {
                _dropRows << insertionIndex + i;
                _originals.insert(insertionIndex + i, fileName);
                i++;
            }
        }
    } else if (parent.isValid()) {
        if (parentInsertionIndex == parent.row()) {
            int i = 0;
            foreach (const QString &fileName, filesToMove) {
                _dropRows << parentInsertionIndex + i;
                _originals.insert(parentInsertionIndex + i, fileName);
                i++;
            }
        } else {
            int i = 0;
            foreach (const QString &fileName, filesToMove) {
                _dropRows << parentInsertionIndex + i + 1;
                _originals.insert(parentInsertionIndex + i + 1, fileName);
                i++;
            }
        }
    } else if (!parent.isValid()) {
        foreach (const QString &fileName, filesToMove) {
            _dropRows << _originals.count();
            _originals << fileName;
        }
    }

    invalidate();

    emit dropDone();

    return false;
}

void FileModel::upRows(const QModelIndexList &indexes) {
    if (!indexes.count())
        return;

    _dropRows.clear();

    QList<int> rows;
    foreach (const QModelIndex &index, indexes)
        rows << index.row();

    qSort(rows);

    if (rows[0] <= 0)
        return;

    foreach (int row, rows) {
        _originals.move(row, row - 1);
        _dropRows << row - 1;
    }

    invalidate();
}

void FileModel::downRows(const QModelIndexList &indexes) {
    if (!indexes.count())
        return;

    _dropRows.clear();

    QList<int> rows;
    foreach (const QModelIndex &index, indexes)
        rows << index.row();

    qSort(rows.begin(), rows.end(), qGreater<int>());

    if (rows[0] >= _originals.count() - 1)
        return;

    foreach (int row, rows) {
        _originals.move(row, row + 1);
        _dropRows << row + 1;
    }

    invalidate();
}

bool caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
    return s1.toLower() < s2.toLower();
}

bool modificationDateLessThan(const QString &fileName1, const QString &fileName2)
{
    return QFileInfo(fileName1).lastModified() < QFileInfo(fileName2).lastModified();
}

void FileModel::sort(SortType sortType) {
    switch (sortType) {
    case SortByName:
        qSort(_originals.begin(), _originals.end(), caseInsensitiveLessThan);
        invalidate();
        break;
    case SortByModificationDate:
        qSort(_originals.begin(), _originals.end(), modificationDateLessThan);
        invalidate();
        break;
    default:;
    }
}
