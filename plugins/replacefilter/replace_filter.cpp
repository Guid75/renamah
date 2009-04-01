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

	_target.setPattern(value);
	emit settingsChanged();
}

void ReplaceFilter::setTargetPatternSyntax(PatternSyntax value) {
	if (_target.patternSyntax() == toQRegExpPatternSyntax(value))
		return;

	_target.setPatternSyntax(toQRegExpPatternSyntax(value));
	emit settingsChanged();
}

void ReplaceFilter::setReplacement(const QString &value) {
	if (_replacement == value)
		return;

	_replacement = value;
	emit settingsChanged();
}

void ReplaceFilter::setCaseSensitive(bool value) {
	if (value && _target.caseSensitivity() == Qt::CaseSensitive)
		return;
	else if (!value && _target.caseSensitivity() == Qt::CaseInsensitive)
		return;

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
