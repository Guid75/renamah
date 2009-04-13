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

#ifndef MODIFIER_FACTORY_H
#define MODIFIER_FACTORY_H

#include "global.h"
#include "plugin.h"
#include "modifier.h"
#include "modifier_config_widget.h"

namespace core
{
	class ModifierFactory : public Plugin
	{
	public:
		/*! Make a new modifier. Just a call to createModifier() and some parentality done */
		Modifier *makeModifier() const {
			Modifier *modifier = createModifier();
			modifier->_factory = const_cast<ModifierFactory*>(this);
			return modifier;
		}

		/*! Returns a configuration QWidget */
		virtual ModifierConfigWidget *makeConfigurationWidget(Modifier *modifier) const { return 0; }

		/*! Deletes the configuration widget in argument (mandatory for shared lib) */
		virtual void deleteConfigurationWidget(QWidget *widget) const { delete widget; }

	protected:
		/*! True method to create a new modifier */
		virtual Modifier *createModifier() const = 0;
	};
};

#endif
