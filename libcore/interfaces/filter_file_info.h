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

#ifndef FILTER_FILE_INFO_H
#define FILTER_FILE_INFO_H

class QString;

namespace core
{
	class FilterFileInfo
	{
	public:
		FilterFileInfo(const QString &originalFilePath,
					   const QString &partToFilter,
					   int fileIndex) {
			this->originalFilePath = originalFilePath;
			this->partToFilter = partToFilter;
			this->fileIndex = fileIndex;
		}

		QString originalFilePath; //!< the complete original file path
		QString partToFilter; //!< the file part to filter
		int fileIndex; //!< the index of the file in all files to filter
	};
};

#endif
