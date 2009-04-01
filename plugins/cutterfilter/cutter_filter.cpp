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

	_startMarkerPosition = value;
	if (correct)
		correctEndMarker();
	emit settingsChanged();
}

void CutterFilter::setStartMarkerIndex(int value, bool correct) {
	if (_startMarkerIndex == value)
		return;

	_startMarkerIndex = value;
	if (correct)
		correctEndMarker();
	emit settingsChanged();
}

void CutterFilter::setEndMarkerPosition(Position value, bool correct) {
	if (_endMarkerPosition == value)
		return;

	_endMarkerPosition = value;
	if (correct)
		correctStartMarker();
	emit settingsChanged();
}

void CutterFilter::setEndMarkerIndex(int value, bool correct) {
	if (_endMarkerIndex == value)
		return;

	_endMarkerIndex = value;
	if (correct)
		correctStartMarker();
	emit settingsChanged();
}

void CutterFilter::setOperation(Operation value) {
	if (_operation == value)
		return;

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
