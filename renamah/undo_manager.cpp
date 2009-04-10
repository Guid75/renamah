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

