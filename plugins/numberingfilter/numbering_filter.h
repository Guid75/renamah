#ifndef NUMBERING_FILTER_H
#define NUMBERING_FILTER_H

#include <QObject>
#include <QRegExp>

#include <interfaces/filter.h>

class NumberingFilter : public core::Filter
{
	Q_OBJECT

	Q_ENUMS(InsertionMode)
	Q_ENUMS(DisplayType)
	Q_PROPERTY(int start READ start WRITE setStart)
	Q_PROPERTY(int step READ step WRITE setStep)
	Q_PROPERTY(QString separator READ separator WRITE setSeparator)
	Q_PROPERTY(DisplayType displayType READ displayType WRITE setDisplayType)
	Q_PROPERTY(int base READ base WRITE setBase)
	Q_PROPERTY(int padding READ padding WRITE setPadding)
	Q_PROPERTY(InsertionMode insertionMode READ insertionMode WRITE setInsertionMode)
	Q_PROPERTY(int customInsertionIndex READ customInsertionIndex WRITE setCustomInsertionIndex)

public:
	enum InsertionMode {
		Prefix,
		Suffix,
		CustomPosition
	};

	enum DisplayType {
		Numeric,
		UpperRoman,
		LowerRoman,
		UpperAlpha,
		LowerAlpha
	};

	NumberingFilter(QObject *parent = 0);

	QString apply(const core::FilterFileInfo &fileInfo) const;

	QString resume() const;

	int start() const { return _start; }
	void setStart(int value);

	int step() const { return _step; }
	void setStep(int value);

	const QString &separator() const { return _separator; }
	void setSeparator(const QString &value);

	DisplayType displayType() const { return _displayType; }
	void setDisplayType(DisplayType value);

	int base() const { return _base; }
	void setBase(int value);

	int padding() const { return _padding; }
	void setPadding(int value);

	InsertionMode insertionMode() const { return _insertionMode; }
	void setInsertionMode(InsertionMode value);

	int customInsertionIndex() const { return _customInsertionIndex; }
	void setCustomInsertionIndex(int value);

private:
	int _start;
	int _step;
	QString _separator;
	DisplayType _displayType;
	int _base;
	int _padding;
	InsertionMode _insertionMode;
	int _customInsertionIndex;

	static QString toRoman(int n);
	static QString toAlphabetic(int n, int padding = 0);
};

#endif
