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

#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include <QUndoStack>
#include <QUndoCommand>
#include <QMap>
#include <QPair>
#include <QVariant>

#include "modifier_model.h"
#include "modifier_manager.h"

class ModifierCommand : public QUndoCommand
{
public:
    ModifierCommand(ModifierModel *model);

    /// undo/redo won't work until this command is activated
    void activate() { _activated = true; }

    void undo();
    void redo();

protected:
    ModifierModel *_model;

    virtual void makeUndo() = 0;
    virtual void makeRedo() = 0;

private:
    bool _activated;
};

class ModifyModifierCommand : public ModifierCommand
{
public:
    ModifyModifierCommand(ModifierModel *model,
                          int modifierIndex,
                          const QMap<QString,QPair<QString,QVariant> > &undoProperties,
                          const QMap<QString,QPair<QString,QVariant> > &redoProperties);

    void makeUndo();
    void makeRedo();

private:
    int _modifierIndex;
    QMap<QString,QPair<QString,QVariant> > _undoProperties;
    QMap<QString,QPair<QString,QVariant> > _redoProperties;
};

class CreateModifierCommand : public ModifierCommand
{
public:
    CreateModifierCommand(ModifierModel *model,
                          ModifierManager *manager,
                          const QString &factoryName);

    void makeUndo();
    void makeRedo();

private:
    ModifierManager *_manager;
    QString _factoryName;
};

class RemoveModifierCommand : public ModifierCommand
{
public:
    RemoveModifierCommand(ModifierModel *model,
                          ModifierManager *manager,
                          int modifierIndex,
                          const QString &factoryName,
                          const QMap<QString,QPair<QString,QVariant> > &properties);

    void makeUndo();
    void makeRedo();

private:
    ModifierManager *_manager;
    int _modifierIndex;
    QString _factoryName;
    QMap<QString,QPair<QString,QVariant> > _properties;
};

class MoveModifierCommand : public ModifierCommand
{
public:
    MoveModifierCommand(ModifierModel *model, int sourceRow, int destinationRow);

    void makeUndo();
    void makeRedo();

private:
    int _sourceRow;
    int _destinationRow;
};

class UndoManager : public QUndoStack
{
    Q_OBJECT

public:
    static UndoManager &instance();

private:
    UndoManager(QObject *parent = 0) : QUndoStack(parent) {}

    static UndoManager *_instance;
};

#endif
