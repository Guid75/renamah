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

#ifndef MODIFIER_MANAGER_H
#define MODIFIER_MANAGER_H

#include <interfaces/modifier_factory.h>

class ModifierManager
{
public:
    void addFactory(core::ModifierFactory *factory);

    core::ModifierFactory *factoryByName(const QString &name) const;

    const QList<core::ModifierFactory*> &factories() const { return _factories; }

    /*! Returns the type name of the modifier created by the factory */
    virtual QString modifierTypeName() = 0;

private:
    QList<core::ModifierFactory*> _factories;
};

#endif
