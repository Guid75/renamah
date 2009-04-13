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

#ifndef PLUGIN_H
#define PLUGIN_H

#include "global.h"
#include "plugin_info.h"

namespace core
{
	class Q_RENAMAH_LIBCORE_EXPORT Plugin
	{
	public:
		/*! Returns all infos relatives to the plugin (name, author, etc) */
		virtual PluginInfo info() const = 0;
	};
};

#endif
