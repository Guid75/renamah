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

#ifndef FILE_MODEL_H
#define FILE_MODEL_H

#include <QAbstractListModel>
#include <QStringList>

class FileModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum SortType {
		SortByName,
		SortByModificationDate
	};

	static FileModel &instance();

	/*! Add a file in the model */
	void addFile(const QString &filePath);

	QString originalFileName(const QModelIndex &index) const;
	QString renamedFileName(const QModelIndex &index) const;

	void setManualRenaming(const QModelIndex &index, const QString &renamedFileName);
	void removeManualRenaming(const QModelIndex &index);

	const QList<int> &dropRows() const { return _dropRows; }
	void upRows(const QModelIndexList &indexes);
	void downRows(const QModelIndexList &indexes);
	void sort(SortType sortType);

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	Qt::ItemFlags flags(const QModelIndex &index) const;
	Qt::DropActions supportedDropActions() const;
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

public slots:
	/*!
	 * \brief (re-)Apply filters on files and eventually generate renamed files
	 */
	void invalidate();

signals:
	void dropDone(); /*!< called when the drop have been successfully done */

private:
	static FileModel *_instance;
	QStringList _originals;
	QMap<QString,QString> _renamedMapping;
	QMap<QString,QString> _manualMapping;
	QList<int> _dropRows;
};

#endif
