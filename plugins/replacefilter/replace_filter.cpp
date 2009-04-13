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

#include "replace_filter.h"

ReplaceFilter::ReplaceFilter(QObject *parent)
	: core::Filter(parent),
	  _target(QRegExp("", Qt::CaseInsensitive, QRegExp::FixedString)) {
}

QString ReplaceFilter::apply(const core::FilterFileInfo &fileInfo) const {
     if (_target.pattern().isEmpty())
          return fileInfo.partToFilter;

	 QString result = fileInfo.partToFilter;
	 return result.replace(_target, _replacement);
}

QString ReplaceFilter::resume() const {
	return _target.pattern() + " -> " + _replacement;
}

void ReplaceFilter::setTargetPattern(const QString &value) {
	if (_target.pattern() == value)
		return;

	emit settingsChanging();
	_target.setPattern(value);
	emit settingsChanged();
}

void ReplaceFilter::setTargetPatternSyntax(PatternSyntax value) {
	if (_target.patternSyntax() == toQRegExpPatternSyntax(value))
		return;

	emit settingsChanging();
	_target.setPatternSyntax(toQRegExpPatternSyntax(value));
	emit settingsChanged();
}

void ReplaceFilter::setReplacement(const QString &value) {
	if (_replacement == value)
		return;

	emit settingsChanging();
	_replacement = value;
	emit settingsChanged();
}

void ReplaceFilter::setCaseSensitive(bool value) {
	if (value && _target.caseSensitivity() == Qt::CaseSensitive)
		return;
	else if (!value && _target.caseSensitivity() == Qt::CaseInsensitive)
		return;

	emit settingsChanging();
	_target.setCaseSensitivity(value ? Qt::CaseSensitive : Qt::CaseInsensitive);
	emit settingsChanged();
}

QRegExp::PatternSyntax ReplaceFilter::toQRegExpPatternSyntax(PatternSyntax patternSyntax) {
	switch (patternSyntax) {
	case RegExp: return QRegExp::RegExp2;
	case Wildcard: return QRegExp::Wildcard;
	case FixedString: return QRegExp::FixedString;
	default: return QRegExp::RegExp2;
	}
}

ReplaceFilter::PatternSyntax ReplaceFilter::toPatternSyntax(QRegExp::PatternSyntax patternSyntax) {
	switch (patternSyntax) {
	case QRegExp::Wildcard: return Wildcard;
	case QRegExp::FixedString: return FixedString;
	default: return RegExp;
	}
}
