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

#include <interfaces/action.h>

#include "action_manager.h"
#include "finalizer_model.h"

FinalizerModel *FinalizerModel::_instance = 0;

FinalizerModel &FinalizerModel::instance()
{
    if (!_instance)
        _instance = new FinalizerModel;

    return *_instance;
}

FinalizerModel::FinalizerModel()
    : ModifierModel(&ActionManager::instance())
{
}

void FinalizerModel::apply(const QString &fileName) const
{
    if (exclusiveModifier())
    {
        static_cast<core::Action*>(exclusiveModifier())->apply(fileName);
        return;
    }

    foreach (core::Modifier *modifier, _modifiers)
    {
        core::Action *action = static_cast<core::Action*>(modifier);
        if (_modifierStates[modifier])
        {
            action->apply(fileName);
        }
    }
}

