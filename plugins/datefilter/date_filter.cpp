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

#include "date_filter.h"

DateFilter::DateFilter(QObject *parent)
	: core::Filter(parent),
	  _type(LastModificationDate),
	  _format(DefaultFormat),
	  _separator("_"),
	  _insertionMode(Suffix),
	  _customInsertionIndex(0) {
}

QString DateFilter::apply(const core::FilterFileInfo &fileInfo) const {
	QString result = fileInfo.partToFilter;

	QFileInfo info(fileInfo.originalFilePath);

	QDateTime dateTime;

	// Get the date time according to the type
	switch (_type) {
	case LastModificationDate:
		dateTime = info.lastModified();
		break;
	case LastAccessDate:
		dateTime = info.lastRead();
		break;
	case CreationDate:
		dateTime = info.created();
		break;
	case CurrentDate:
		dateTime = QDateTime::currentDateTime();
		break;
	case CustomDate:
		dateTime = _customDateTime;
		break;
	default:
		return result;
	}

	QString text;
	if (_format == CustomFormat)
		text = dateTime.toString(_customFormat);
	else
		text = dateTime.toString(formatToQtDateFormat(_format));

	switch (_insertionMode) {
	case Prefix:
		return QString("%1%2%3").arg(text).arg(_separator).arg(fileInfo.partToFilter);
	case Suffix:
		return QString("%1%2%3").arg(fileInfo.partToFilter).arg(_separator).arg(text);
	case CustomPosition:
	{
		QString result = fileInfo.partToFilter;
		QString insertionText = text;
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

QString DateFilter::resume() const {
//	"Keep from 1 (from left) to 7 (from right)
	return typeToString(_type);
}

void DateFilter::setType(Type value) {
	if (_type == value)
		return;

	emit settingsChanging();
	_type = value;
	emit settingsChanged();
}

void DateFilter::setCustomDateTime(const QDateTime &value) {
	if (_customDateTime == value)
		return;

	emit settingsChanging();
	_customDateTime = value;
	emit settingsChanged();
}

void DateFilter::setFormat(Format value) {
	if (_format == value)
		return;

	emit settingsChanging();
	_format = value;
	emit settingsChanged();
}

void DateFilter::setCustomFormat(const QString &value) {
	if (_customFormat == value)
		return;

	emit settingsChanging();
	_customFormat = value;
	emit settingsChanged();
}

void DateFilter::setSeparator(const QString &value) {
	if (_separator == value)
		return;

	emit settingsChanging();
	_separator = value;
	emit settingsChanged();
}

void DateFilter::setInsertionMode(InsertionMode value) {
	if (_insertionMode == value)
		return;

	emit settingsChanging();
	_insertionMode = value;
	emit settingsChanged();
}

void DateFilter::setCustomInsertionIndex(int value) {
	if (_customInsertionIndex == value)
		return;

	emit settingsChanging();
	_customInsertionIndex = value;
	emit settingsChanged();
}

Qt::DateFormat DateFilter::formatToQtDateFormat(Format format) {
	switch (format) {
	case DefaultFormat: return Qt::TextDate;
	case ISOFormat: return Qt::ISODate;
	default:;
	}
	return Qt::TextDate;
}

QString DateFilter::typeToString(Type type) {
	switch (type) {
	case LastModificationDate: return tr("Last modification");
	case LastAccessDate: return tr("Last access");
	case CreationDate: return tr("Creation");
	case CurrentDate: return tr("Current");
	case CustomDate: return tr("Custom");
	default:;
	}
	return "";
}
