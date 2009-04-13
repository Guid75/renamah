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

#ifndef FILTER_FACTORY_H
#define FILTER_FACTORY_H

#include "global.h"
#include "modifier_factory.h"
#include "filter.h"

namespace core
{
	class FilterFactory : public ModifierFactory
	{
	protected:
		Modifier *createModifier() const { return createFilter(); }

		/*! True method to create a new filter */
		virtual Filter *createFilter() const = 0;
	};
};

Q_DECLARE_INTERFACE(core::FilterFactory,
                    "fr.free.guillaume.denry.Renamah.FilterFactory/1.0")

#endif
