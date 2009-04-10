#include "numbering_filter.h"

NumberingFilter::NumberingFilter(QObject *parent)
	: core::Filter(parent),
	  _start(1), _step(1), _separator("_"), _displayType(Numeric), _base(10), _padding(0),
	  _insertionMode(Prefix), _customInsertionIndex(0) {
}

QString NumberingFilter::apply(const core::FilterFileInfo &fileInfo) const {
	QString trueIndex;
	switch (_displayType) {
	case Numeric:
		trueIndex = QString("%1").arg(_start + _step * fileInfo.fileIndex, _padding,
									  _base, QChar('0')).toUpper();
		break;
	case UpperRoman:
		trueIndex = toRoman(_start + _step * fileInfo.fileIndex);
		break;
	case LowerRoman:
		trueIndex = toRoman(_start + _step * fileInfo.fileIndex).toLower();
		break;
	case UpperAlpha:
		trueIndex = toAlphabetic(_start + _step * fileInfo.fileIndex, _padding);
		break;
	case LowerAlpha:
		trueIndex = toAlphabetic(_start + _step * fileInfo.fileIndex, _padding).toLower();
		break;
	default:;
	}

	switch (_insertionMode) {
	case Prefix:
		return QString("%1%2%3").arg(trueIndex).arg(_separator).arg(fileInfo.partToFilter);
	case Suffix:
		return QString("%1%2%3").arg(fileInfo.partToFilter).arg(_separator).arg(trueIndex);
	case CustomPosition:
	{
		QString result = fileInfo.partToFilter;
		QString insertionText = trueIndex;
		if (_customInsertionIndex > 0)
			insertionText = _separator + insertionText;
		if (_customInsertionIndex <= result.length() - 1)
			insertionText += _separator;
		return result.insert(_customInsertionIndex, insertionText);
	}
	default:;
	}
	return fileInfo.partToFilter;
}

QString NumberingFilter::resume() const {
	return tr("Start: %1, Step: %2").arg(_start).arg(_step);
}

QString NumberingFilter::toRoman(int n) {
	QString result;
	static int values[] = { 1000, 900, 500, 400, 100,90, 50, 40, 10, 9, 5, 4, 1 };
	static QString numerals[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
	for (int i = 0; i < 13; i++) {
		while (n >= values[i]) {
			n -= values[i];
			result += numerals[i];
		}
	}
	return result;
}

QString NumberingFilter::toAlphabetic(int n, int padding)
{
	QString result;
	do {
		int q = n / 26;
		int r = n - (q * 26);
		result = QChar('A' + r) + result;
		n = q;
	} while (n);

	if (result.length() < padding)
		result = QString(padding - result.length(), 'A') + result;

	return result;
}

void NumberingFilter::setStart(int value) {
	if (_start == value)
		return;

	emit settingsChanging();
	_start = value;
	emit settingsChanged();
}

void NumberingFilter::setStep(int value) {
	if (_step == value)
		return;

	emit settingsChanging();
	_step = value;
	emit settingsChanged();
}

void NumberingFilter::setSeparator(const QString &value) {
	if (_separator == value)
		return;

	emit settingsChanging();
	_separator = value;
	emit settingsChanged();
}

void NumberingFilter::setDisplayType(DisplayType value) {
	if (_displayType == value)
		return;

	emit settingsChanging();
	_displayType = value;
	emit settingsChanged();
}

void NumberingFilter::setBase(int value) {
	if (_base == value)
		return;

	emit settingsChanging();
	_base = value;
	emit settingsChanged();
}

void NumberingFilter::setPadding(int value) {
	if (_padding == value)
		return;

	emit settingsChanging();
	_padding = value;
	emit settingsChanged();
}

void NumberingFilter::setInsertionMode(InsertionMode value) {
	if (_insertionMode == value)
		return;

	emit settingsChanging();
	_insertionMode = value;
	emit settingsChanged();
}

void NumberingFilter::setCustomInsertionIndex(int value) {
	if (_customInsertionIndex == value)
		return;

	emit settingsChanging();
	_customInsertionIndex = value;
	emit settingsChanged();
}
