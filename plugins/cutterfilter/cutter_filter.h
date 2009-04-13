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

#ifndef CUTTER_FILTER_H
#define CUTTER_FILTER_H

#include <QObject>
#include <QRegExp>

#include <interfaces/filter.h>

class CutterFilter : public core::Filter
{
	Q_OBJECT

	Q_ENUMS(Position)
	Q_ENUMS(Operation)
	Q_PROPERTY(Position startMarkerPosition READ startMarkerPosition WRITE setStartMarkerPosition)
	Q_PROPERTY(int startMarkerIndex READ startMarkerIndex WRITE setStartMarkerIndex)
	Q_PROPERTY(Position endMarkerPosition READ endMarkerPosition WRITE setEndMarkerPosition)
	Q_PROPERTY(int endMarkerIndex READ endMarkerIndex WRITE setEndMarkerIndex)
	Q_PROPERTY(Operation operation READ operation WRITE setOperation)

public:
	enum Position {
		FromLeft,
		FromRight
	};

	enum Operation {
		Keep,
		Remove
	};

	CutterFilter(QObject *parent = 0);

	QString apply(const core::FilterFileInfo &fileInfo) const;

	QString resume() const;

	Position startMarkerPosition() const { return _startMarkerPosition; }
	void setStartMarkerPosition(Position value, bool correct = false);

	int startMarkerIndex() const { return _startMarkerIndex; }
	void setStartMarkerIndex(int value, bool correct = false);

	Position endMarkerPosition() const { return _endMarkerPosition; }
	void setEndMarkerPosition(Position value, bool correct = false);

	int endMarkerIndex() const { return _endMarkerIndex; }
	void setEndMarkerIndex(int value, bool correct = false);

	Operation operation() const { return _operation; }
	void setOperation(Operation value);

private:
	Position _startMarkerPosition;
	int _startMarkerIndex;

	Position _endMarkerPosition;
	int _endMarkerIndex;

	Operation _operation;

	void correctStartMarker();
	void correctEndMarker();
};

#endif
