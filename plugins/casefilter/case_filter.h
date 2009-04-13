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

#ifndef CASE_FILTER_H
#define CASE_FILTER_H

#include <QRegExp>

#include <interfaces/filter.h>

class CaseFilter : public core::Filter
{
	Q_OBJECT

	Q_ENUMS(Operation)
	Q_PROPERTY(Operation operation READ operation WRITE setOperation)
	Q_PROPERTY(bool lowerOtherChars READ lowerOtherChars WRITE setLowerOtherChars)

public:
	enum Operation {
		Operation_Begin,

		LowerCase = Operation_Begin,
		UpperCase,
		UpFirstLetter,
		UpWordsFirstLetter,

		Operation_End
	};

	CaseFilter(QObject *parent = 0) :
		core::Filter(parent),
		_operation(LowerCase),
		_lowerOtherChars(true) {}

	Operation operation() const { return _operation; }
	void setOperation(Operation value);

	static QString operationCaption(Operation operation);

	bool lowerOtherChars() const { return _lowerOtherChars; }
	void setLowerOtherChars(bool value);

	QString apply(const core::FilterFileInfo &fileInfo) const;

	QString resume() const;

private:
	Operation _operation;
	bool _lowerOtherChars;
};

#endif
