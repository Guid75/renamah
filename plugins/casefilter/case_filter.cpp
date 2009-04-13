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

#include <QFileInfo>
#include <QDir>
#include <QTextBoundaryFinder>

#include "case_filter.h"

QString CaseFilter::apply(const core::FilterFileInfo &fileInfo) const {
	QString result = fileInfo.partToFilter;

	switch (_operation)
	{
	case LowerCase:
		result = result.toLower();
		break;
	case UpperCase:
		result = result.toUpper();
		break;
	case UpFirstLetter:
		if (result.length()) {
			if (_lowerOtherChars)
				result = result[0].toUpper() +
					result.mid(1, result.length() - 1).toLower();
			else
				result[0] = result[0].toUpper();
		}
		break;
	case UpWordsFirstLetter:
	{
		QTextBoundaryFinder finder(QTextBoundaryFinder::Word, result);
		int p;
		int start = 1;
		if (finder.isAtBoundary())
			result[0] = result[0].toUpper();

		while ((p = finder.toNextBoundary()) >= 0)
		{
			if (finder.boundaryReasons() & QTextBoundaryFinder::StartWord)
			{
				start = p + 1;
				result[p] = result[p].toUpper();
			} else if (finder.boundaryReasons() & QTextBoundaryFinder::EndWord &&
					   p >= start &&
					   _lowerOtherChars)
			{
				result.replace(start, p - start, result.mid(start, p - start).toLower());
			}
		}
		break;
	}
	default:;
	}

	return result;
}

QString CaseFilter::operationCaption(Operation operation)
{
	switch (operation)
	{
	case LowerCase: return tr("lower case", "case counts!");
	case UpperCase: return tr("UPPER CASE", "case counts!");
	case UpFirstLetter: return tr("First letter in upcase", "case counts!");
	case UpWordsFirstLetter: return tr("Words First Letter In Upcase", "case counts!");
	default: return "";
	}
}

QString CaseFilter::resume() const
{
	return operationCaption(_operation);
}

void CaseFilter::setOperation(Operation value) {
	if (_operation == value)
		return;

	emit settingsChanging();
	_operation = value;
	emit settingsChanged();
}

void CaseFilter::setLowerOtherChars(bool value) {
	if (_lowerOtherChars == value)
		return;

	emit settingsChanging();
	_lowerOtherChars = value;
	emit settingsChanged();
}

