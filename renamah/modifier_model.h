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

#ifndef MODIFIER_MODEL_H
#define MODIFIER_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include <interfaces/filter.h>

#include "modifier_manager.h"

class ModifierModel : public QAbstractListModel
{
    Q_OBJECT

public:
    static const int colIndex = 3;
    static const int colMode = 0;
    static const int colCaption = 1;
    static const int columnNumber = 2;

    ModifierModel(ModifierManager *manager);

    /** Returns a modifier in function of a model index */
    core::Modifier *modifier(const QModelIndex &index) const;

    /** Add a modifier to the model */
    void addModifier(core::Modifier *modifier);

    /** Insert a modifier into the model */
    void insertModifier(int index, core::Modifier *modifier);

    /*! Remove the modifier at <index> */
    void removeModifier(const QModelIndex &index);

    /*! Clear all modifiers */
    virtual void clear();

    /*! Returns the modifier state */
    bool modifierState(core::Modifier *modifier) const;

    /*! Activate or deactivate a modifier */
    void setModifierState(core::Modifier *modifier, bool state);

    /*! Toggle the state of the modifier */
    void toggleModifierState(core::Modifier *modifier);

    /*! Set a modifier as the uniq modifier, deactivate others */
    void setExclusiveModifier(core::Modifier *modifier);

    /*! If modifier was not exclusive => set it exclusive */
    void toggleExclusiveState(core::Modifier *modifier);

    /** Move a modifier from a place to another
	 * destination can be >= rowCount(), in this case, the modifier is moved at the list tail
	 */
    void moveModifier(int source, int destination);

    /*! Returns the exclusive modifier */
    core::Modifier *exclusiveModifier() const { return _exclusiveModifier; }

    void refreshLayout() { emit layoutChanged(); }

    void beginUndoAction(); // Must be called just before the undo manager makes an undo or a redo action
    void endUndoAction(); // Must be called just after the undo manager makes an undo or a redo action

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    Qt::DropActions supportedDropActions() const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

signals:
    void modifiersChanged();

protected:
    ModifierManager *_manager;
    QList<core::Modifier*> _modifiers;
    QMap<core::Modifier*, bool> _modifierStates;
    core::Modifier *_exclusiveModifier;
    QMap<QString,QPair<QString,QVariant> > _changingModifierOldProperties;

private:
    bool _disableUndo;

    void init(core::Modifier *modifier);

private slots:
    void modifierChanging();
    void modifierChanged();
};

#endif
