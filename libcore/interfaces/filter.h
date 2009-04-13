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

#ifndef FILTER_H
#define FILTER_H

class QString;

#include "global.h"
#include "modifier.h"
#include "filter_file_info.h"

namespace core
{
	class Q_RENAMAH_LIBCORE_EXPORT Filter : public Modifier
	{
		Q_OBJECT

	public:
		Filter(QObject *parent = 0) : Modifier(parent) {}

		/*! Returns the filtered string of the parameter partToFilter which is a part of the parameter filePath
		 * \param partToFilter The filename part to filter
		 * \param filePath the complete file path
		 */
		virtual QString apply(const FilterFileInfo &fileInfo) const = 0;
	};
};

#endif
