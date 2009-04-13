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

#ifndef REPLACE_FILTER_H
#define REPLACE_FILTER_H

#include <QObject>
#include <QRegExp>

#include <interfaces/filter.h>

class ReplaceFilter : public core::Filter
{
	Q_OBJECT

	Q_ENUMS(PatternSyntax)
	Q_PROPERTY(QString targetPattern READ targetPattern WRITE setTargetPattern)
	Q_PROPERTY(PatternSyntax targetPatternSyntax READ targetPatternSyntax WRITE setTargetPatternSyntax)
	Q_PROPERTY(QString replacement READ replacement WRITE setReplacement)
	Q_PROPERTY(bool caseSensitive READ caseSensitive WRITE setCaseSensitive)

public:
	enum PatternSyntax {
		RegExp,
		Wildcard,
		FixedString
	};

	ReplaceFilter(QObject *parent = 0);

	QString apply(const core::FilterFileInfo &fileInfo) const;

	QString resume() const;

	QString targetPattern() const { return _target.pattern(); }
	void setTargetPattern(const QString &value);

	PatternSyntax targetPatternSyntax() const { return toPatternSyntax(_target.patternSyntax()); }
	void setTargetPatternSyntax(PatternSyntax value);

	const QString &replacement() const { return _replacement; }
	void setReplacement(const QString &value);

	bool caseSensitive() const { return _target.caseSensitivity() == Qt::CaseSensitive; }
	void setCaseSensitive(bool value);

private:
	QRegExp _target;
	QString _replacement;

	static QRegExp::PatternSyntax toQRegExpPatternSyntax(PatternSyntax patternSyntax);
	static PatternSyntax toPatternSyntax(QRegExp::PatternSyntax patternSyntax);
};

#endif
