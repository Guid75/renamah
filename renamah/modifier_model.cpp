#include <QMimeData>

#include <interfaces/modifier_factory.h>

#include "modifier_model.h"

ModifierModel::ModifierModel()
	: _exclusiveModifier(0)
{
}

int ModifierModel::rowCount(const QModelIndex &parent) const
{
	return _modifiers.count();
}

int ModifierModel::columnCount(const QModelIndex &parent) const
{
	return columnNumber;
}

QVariant ModifierModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid() || index.row() < 0 || index.row() >= _modifiers.count())
		return QVariant();

	const core::Modifier *modifier = _modifiers[index.row()];
	switch (role)
	{
	case Qt::DisplayRole:
		switch (index.column())
		{
		case colIndex: return index.row() + 1;
		case colMode: return "";
		case colCaption: return modifier->factory()->info().caption() + " [" + modifier->resume() + "]";
		default:;
		}
	case Qt::ForegroundRole:
		if (_exclusiveModifier && _exclusiveModifier != modifier)
			return Qt::gray;
		break;
	default:;
	}
	return QVariant();
}

QVariant ModifierModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	switch (role)
	{
	case Qt::DisplayRole:
		switch (section)
		{
		case colIndex: return tr("#");
		case colMode: return tr("Mode");
		case colCaption: return tr("Action");
		default:;
		}
		break;
	default:;
	}
	return QVariant();
}

void ModifierModel::addModifier(core::Modifier *modifier)
{
	connect(modifier, SIGNAL(settingsChanged()), this, SIGNAL(modifiersChanged()));

	beginInsertRows(QModelIndex(), _modifiers.count(), _modifiers.count());
	_modifiers << modifier;
	_modifierStates[modifier] = true;
	endInsertRows();

	emit modifiersChanged();
}

void ModifierModel::removeModifier(const QModelIndex &index)
{
	if (!index.isValid())
		return;

	removeRows(index.row(), 1);
}

bool ModifierModel::modifierState(core::Modifier *modifier) const
{
	if (_modifierStates.find(modifier) == _modifierStates.end())
		return false;
	else
		return _modifierStates[modifier];
}

void ModifierModel::setModifierState(core::Modifier *modifier, bool state)
{
	int modifierRow = _modifiers.indexOf(modifier);
	if (modifierRow < 0)
		return;

	if (_modifierStates[modifier] != state)
	{
		_modifierStates[modifier] = state;
		emit dataChanged(index(modifierRow, 0), index(modifierRow, columnNumber - 1));
		emit modifiersChanged();
	}
}

void ModifierModel::toggleModifierState(core::Modifier *modifier)
{
	if (_modifierStates.find(modifier) == _modifierStates.end())
		return;

	setModifierState(modifier, !_modifierStates[modifier]);
}

void ModifierModel::setExclusiveModifier(core::Modifier *modifier)
{
	if (_exclusiveModifier == modifier)
		return;

	_exclusiveModifier = modifier;
	if (modifier)
		_modifierStates[modifier] = true;

	// Refresh all
	emit dataChanged(index(0, 0), index(rowCount() - 1, columnNumber - 1));
	emit modifiersChanged();
}

/*QString ModifierModel::apply(const QString &str) const
{
	if (_exclusiveModifier)
		return _exclusiveModifier->apply(str);

	QString filtered = str;

	foreach (core::Filter *filter, _modifiers)
		if (_modifierstates[filter])
			filtered = filter->apply(filtered);

	return filtered;
	}*/

core::Modifier *ModifierModel::modifier(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	if (index.row() >= 0 && index.row() < rowCount())
		return _modifiers[index.row()];
}

Qt::ItemFlags ModifierModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags flags = QAbstractListModel::flags(index);

     if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | flags;
     else
         return Qt::ItemIsDropEnabled | flags;
}

void ModifierModel::toggleExclusiveState(core::Modifier *modifier)
{
	if (_exclusiveModifier == modifier)
		_exclusiveModifier = 0;
	else
		_exclusiveModifier = modifier;

	if (_exclusiveModifier)
		_modifierStates[_exclusiveModifier] = true;

	// Refresh all
	emit dataChanged(index(0, 0), index(rowCount() - 1, columnNumber - 1));
	emit modifiersChanged();
}

bool ModifierModel::upModifier(const QModelIndex &modifierIndex)
{
	if (!modifierIndex.row())
		return false;

	_modifiers.swap(modifierIndex.row(), modifierIndex.row() - 1);
	emit dataChanged(index(modifierIndex.row() - 1, 0),
					 index(modifierIndex.row(), columnNumber - 1));
	emit modifiersChanged();
	return true;
}

bool ModifierModel::downModifier(const QModelIndex &modifierIndex)
{
	if (modifierIndex.row() == rowCount() - 1)
		return false;

	_modifiers.swap(modifierIndex.row(), modifierIndex.row() + 1);
	emit dataChanged(index(modifierIndex.row(), 0),
					 index(modifierIndex.row() + 1, columnNumber - 1));
	emit modifiersChanged();
	return true;
}

Qt::DropActions ModifierModel::supportedDropActions() const {
	return Qt::MoveAction;
}

bool ModifierModel::removeRows(int row, int count, const QModelIndex &parent) {
	core::Modifier *modifierToRemove = modifier(index(row, 0));

	beginRemoveRows(QModelIndex(), row, row);

	_modifiers.removeAt(_modifiers.indexOf(modifierToRemove));
	_modifierStates.remove(modifierToRemove);
	if (_exclusiveModifier == modifierToRemove)
		_exclusiveModifier = 0;
	delete modifierToRemove;

	endRemoveRows();

	emit modifiersChanged();
}

#define MIMETYPE QLatin1String("filter-rows")

QStringList ModifierModel::mimeTypes() const
{
	QStringList types;
	types << MIMETYPE;
	return types;
}

QMimeData *ModifierModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData *mimeData = new QMimeData;
	QByteArray encodedData;

	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	foreach (QModelIndex index, indexes) {
		if (index.isValid()) {
			stream << index.row();
		}
	}

	mimeData->setData(MIMETYPE, encodedData);
	return mimeData;
}

bool ModifierModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) {
	if (action == Qt::IgnoreAction)
		return false;

	QByteArray inData = data->data(MIMETYPE);
	QDataStream stream(inData);
	int r;
	stream >> r;

	core::Modifier *modifier = _modifiers[r];

	if (row != -1) {
		if (row >= rowCount()) {
			_modifiers.takeAt(r);
			_modifiers << modifier;
			_dropRow = rowCount() - 1;
		} else {
			if (r < row)
				row--;
			_modifiers.move(r, row);
			_dropRow = row;
		}
	} else if (parent.isValid()) {
		_modifiers.move(r, parent.row());
		_dropRow = parent.row();
	} else if (!parent.isValid()) {
		_modifiers.takeAt(r);
		_modifiers << modifier;
		_dropRow = rowCount() - 1;
	}

	emit modifiersChanged();
	emit dropDone();

	return false;
}

void ModifierModel::clear() {
	_exclusiveModifier = 0;
	qDeleteAll(_modifiers);
	_modifiers.clear();
	_modifierStates.clear();
	reset();
	emit modifiersChanged();
}
