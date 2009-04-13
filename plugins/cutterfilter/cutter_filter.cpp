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

#include "cutter_filter.h"

CutterFilter::CutterFilter(QObject *parent)
	: core::Filter(parent),
	  _startMarkerPosition(FromLeft),
	  _startMarkerIndex(1),
	  _endMarkerPosition(FromRight),
	  _endMarkerIndex(1),
	  _operation(Keep)
{
}

QString CutterFilter::apply(const core::FilterFileInfo &fileInfo) const {
	QString result = fileInfo.partToFilter;

	int trueStartIndex = _startMarkerPosition == FromRight ?
		result.length() - _startMarkerIndex + 1 : _startMarkerIndex;

	int trueEndIndex = _endMarkerPosition == FromRight ?
		result.length() - _endMarkerIndex + 1 : _endMarkerIndex;

	if (trueEndIndex < trueStartIndex) // Impossible case
		return result;

	switch (_operation) {
	case Keep:
		result = result.mid(trueStartIndex - 1, trueEndIndex - trueStartIndex + 1);
		break;
	case Remove:
		result = result.remove(trueStartIndex - 1, trueEndIndex - trueStartIndex + 1);
		break;
	default:;
	}

	return result;
}

QString CutterFilter::resume() const {
//	"Keep from 1 (from left) to 7 (from right)
	return "TODO";
}

void CutterFilter::setStartMarkerPosition(Position value, bool correct) {
	if (_startMarkerPosition == value)
		return;

	emit settingsChanging();
	_startMarkerPosition = value;
	if (correct)
		correctEndMarker();
	emit settingsChanged();
}

void CutterFilter::setStartMarkerIndex(int value, bool correct) {
	if (_startMarkerIndex == value)
		return;

	emit settingsChanging();
	_startMarkerIndex = value;
	if (correct)
		correctEndMarker();
	emit settingsChanged();
}

void CutterFilter::setEndMarkerPosition(Position value, bool correct) {
	if (_endMarkerPosition == value)
		return;

	emit settingsChanging();
	_endMarkerPosition = value;
	if (correct)
		correctStartMarker();
	emit settingsChanged();
}

void CutterFilter::setEndMarkerIndex(int value, bool correct) {
	if (_endMarkerIndex == value)
		return;

	emit settingsChanging();
	_endMarkerIndex = value;
	if (correct)
		correctStartMarker();
	emit settingsChanged();
}

void CutterFilter::setOperation(Operation value) {
	if (_operation == value)
		return;

	emit settingsChanging();
	_operation = value;
	emit settingsChanged();
}

void CutterFilter::correctStartMarker() {
	switch (_endMarkerPosition) {
	case FromLeft:
		if (_startMarkerPosition == FromRight)
			_startMarkerPosition = FromLeft;

		if (_startMarkerPosition == FromLeft &&	_startMarkerIndex > _endMarkerIndex)
			_startMarkerIndex = _endMarkerIndex;
		break;
	case FromRight:
		if (_startMarkerPosition == FromRight && _startMarkerIndex < _endMarkerIndex)
			_startMarkerIndex = _endMarkerIndex;
		break;
	default:;
	}
}

void CutterFilter::correctEndMarker() {
	switch (_startMarkerPosition) {
	case FromLeft:
		if (_endMarkerPosition == FromLeft && _endMarkerIndex < _startMarkerIndex)
			_endMarkerIndex = _startMarkerIndex;
		break;
	case FromRight:
		if (_endMarkerPosition == FromLeft)
			_endMarkerPosition = FromRight;

		if (_endMarkerPosition == FromRight && _endMarkerIndex > _startMarkerIndex)
			_endMarkerIndex = _startMarkerIndex;
		break;
	}
}
