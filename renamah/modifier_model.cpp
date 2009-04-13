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

#include <QMimeData>

#include <interfaces/modifier_factory.h>

#include "undo_manager.h"
#include "modifier_model.h"

ModifierModel::ModifierModel(ModifierManager *manager)
	: _manager(manager),
	  _exclusiveModifier(0),
	  _disableUndo(false)
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

void ModifierModel::init(core::Modifier *modifier) {
	connect(modifier, SIGNAL(settingsChanging()), this, SLOT(modifierChanging()));
	connect(modifier, SIGNAL(settingsChanged()), this, SLOT(modifierChanged()));
	connect(modifier, SIGNAL(settingsChanged()), this, SIGNAL(modifiersChanged()));
}

void ModifierModel::addModifier(core::Modifier *modifier)
{
	init(modifier);

	beginInsertRows(QModelIndex(), _modifiers.count(), _modifiers.count());
	_modifiers << modifier;
	_modifierStates[modifier] = true;
	endInsertRows();

	if (!_disableUndo) {
		CreateModifierCommand *command = new CreateModifierCommand(this, _manager, modifier->factory()->info().name());
		UndoManager::instance().push(command);
		command->activate();
	}

	emit modifiersChanged();
}

void ModifierModel::insertModifier(int index, core::Modifier *modifier) {
	init(modifier);

	beginInsertRows(QModelIndex(), index, index);
	_modifiers.insert(index, modifier);
	_modifierStates[modifier] = true;
	endInsertRows();

	// TODO : integrate into the undo framework!!!

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

Qt::DropActions ModifierModel::supportedDropActions() const {
	return Qt::MoveAction;
}

bool ModifierModel::removeRows(int row, int count, const QModelIndex &parent) {
	core::Modifier *modifierToRemove = modifier(index(row, 0));

	if (!_disableUndo) {
		RemoveModifierCommand *command = new RemoveModifierCommand(this, _manager, row, modifierToRemove->factory()->info().name(),
																   modifierToRemove->serializeProperties());
		UndoManager::instance().push(command);
		command->activate();
	}

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
	int sourceRow;
	stream >> sourceRow;

	int destinationRow = rowCount();

	if (row != -1) {
		if (row >= rowCount()) {
			destinationRow = rowCount();
		} else {
			if (sourceRow < row)
				row--;
			destinationRow = row;
		}
	} else if (parent.isValid()) {
		destinationRow = parent.row();
	} else if (!parent.isValid()) {
		destinationRow = rowCount();
	}

	moveModifier(sourceRow, destinationRow);

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

void ModifierModel::modifierChanged() {
	if (_disableUndo)
		return;

	core::Modifier *modifier = static_cast<core::Modifier*>(sender());

	// Undo managing => compute the diff
	QMap<QString,QPair<QString,QVariant> > newProperties = modifier->serializeProperties();
	QMap<QString,QPair<QString,QVariant> > &oldProperties = _changingModifierOldProperties;
	QMap<QString,QPair<QString,QVariant> > undoProperties, redoProperties;

	foreach (const QString &propName, newProperties.keys()) {
		QPair<QString,QVariant> &newPair = newProperties[propName];
		QPair<QString,QVariant> &oldPair = oldProperties[propName];

		if (newPair != oldPair) {
			undoProperties.insert(propName, oldPair);
			redoProperties.insert(propName, newPair);
		}
	}

	ModifyModifierCommand *command = new ModifyModifierCommand(this, _modifiers.indexOf(modifier), undoProperties, redoProperties);
	UndoManager::instance().push(command);
	command->activate();
}

void ModifierModel::modifierChanging() {
	if (_disableUndo)
		return;

	core::Modifier *modifier = static_cast<core::Modifier*>(sender());

	_changingModifierOldProperties = modifier->serializeProperties();
}

void ModifierModel::beginUndoAction() {
	_disableUndo = true;
}

void ModifierModel::endUndoAction() {
	_disableUndo = false;
}

void ModifierModel::moveModifier(int sourceRow, int destinationRow) {
	Q_ASSERT_X(sourceRow >= 0 && sourceRow < rowCount(), "ModifierModel::moveModifier()", qPrintable(QString("<sourceRow> is out of bound: %d!").arg(sourceRow)));

	if (sourceRow == destinationRow) // Save destination => do nothing
		return;

	if (destinationRow >= rowCount() - 1 &&
		sourceRow == rowCount() - 1) // Already at the list queue => do nothing
		return;

	beginRemoveRows(QModelIndex(), sourceRow, sourceRow);
	core::Modifier *modifier = _modifiers.takeAt(sourceRow);
	endRemoveRows();
	beginInsertRows(QModelIndex(), destinationRow, destinationRow);
	_modifiers.insert(destinationRow, modifier);
	endInsertRows();

	emit modifiersChanged();

	if (!_disableUndo) {
		MoveModifierCommand *command = new MoveModifierCommand(this, sourceRow, destinationRow);
		UndoManager::instance().push(command);
		command->activate();
	}
}
