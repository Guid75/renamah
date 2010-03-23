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

#include "undo_manager.h"

UndoManager *UndoManager::_instance = 0;

UndoManager &UndoManager::instance() {
    if (!_instance)
        _instance = new UndoManager;

    return *_instance;
}

/////////////////////////////////
/// ModifierCommand /////////////
/////////////////////////////////

ModifierCommand::ModifierCommand(ModifierModel *model)
    : _model(model),
    _activated(false) {
}

void ModifierCommand::undo() {
    if (!_activated)
        return;

    _model->beginUndoAction();
    makeUndo();
    _model->endUndoAction();
}

void ModifierCommand::redo() {
    if (!_activated)
        return;

    _model->beginUndoAction();
    makeRedo();
    _model->endUndoAction();
}

/////////////////////////////////
/// ModifyModifierCommand ///////
/////////////////////////////////

ModifyModifierCommand::ModifyModifierCommand(ModifierModel *model,
                                             int modifierIndex,
                                             const QMap<QString,QPair<QString,QVariant> > &undoProperties,
                                             const QMap<QString,QPair<QString,QVariant> > &redoProperties)
                                                 : ModifierCommand(model),
                                                 _modifierIndex(modifierIndex),
                                                 _undoProperties(undoProperties),
                                                 _redoProperties(redoProperties) {
    setText("Modifier modification");
}

void ModifyModifierCommand::makeUndo() {
    core::Modifier *modifier = _model->modifier(_model->index(_modifierIndex, 0));
    modifier->deserializeProperties(_undoProperties);
}

void ModifyModifierCommand::makeRedo() {
    core::Modifier *modifier = _model->modifier(_model->index(_modifierIndex, 0));
    modifier->deserializeProperties(_redoProperties);
}

/////////////////////////////////
/// CreateModifierCommand ///////
/////////////////////////////////

CreateModifierCommand::CreateModifierCommand(ModifierModel *model,
                                             ModifierManager *manager,
                                             const QString &factoryName)
                                                 : ModifierCommand(model),
                                                 _manager(manager),
                                                 _factoryName(factoryName) {
    setText("Modifier creation");
}

void CreateModifierCommand::makeUndo() {
    _model->removeModifier(_model->index(_model->rowCount() - 1, 0));
}

void CreateModifierCommand::makeRedo() {
    core::ModifierFactory *factory = _manager->factoryByName(_factoryName);
    core::Modifier *modifier = factory->makeModifier();
    _model->addModifier(modifier);
}

/////////////////////////////////
/// RemoveModifierCommand ///////
/////////////////////////////////

RemoveModifierCommand::RemoveModifierCommand(ModifierModel *model,
                                             ModifierManager *manager,
                                             int modifierIndex,
                                             const QString &factoryName,
                                             const QMap<QString,QPair<QString,QVariant> > &properties)
                                                 : ModifierCommand(model),
                                                 _manager(manager),
                                                 _modifierIndex(modifierIndex),
                                                 _factoryName(factoryName),
                                                 _properties(properties) {
    setText("Modifier removing");
}

void RemoveModifierCommand::makeUndo() {
    core::ModifierFactory *factory = _manager->factoryByName(_factoryName);
    core::Modifier *modifier = factory->makeModifier();
    modifier->deserializeProperties(_properties);
    _model->insertModifier(_modifierIndex, modifier);
}

void RemoveModifierCommand::makeRedo() {
    _model->removeModifier(_model->index(_modifierIndex, 0));
}

/////////////////////////////////
/// MoveModifierCommand /////////
/////////////////////////////////

MoveModifierCommand::MoveModifierCommand(ModifierModel *model, int sourceRow, int destinationRow)
    : ModifierCommand(model),
    _sourceRow(sourceRow),
    _destinationRow(destinationRow) {
    setText("Modifier move");
}

void MoveModifierCommand::makeUndo() {
    if (_destinationRow >= _model->rowCount())
        _model->moveModifier(_model->rowCount() - 1, _sourceRow);
    else
        _model->moveModifier(_destinationRow, _sourceRow);
}

void MoveModifierCommand::makeRedo() {
    _model->moveModifier(_sourceRow, _destinationRow);
}
