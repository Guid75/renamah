#ifndef DATE_FILTER_H
#define DATE_FILTER_H

#include <QDateTime>

#include <interfaces/filter.h>

class DateFilter : public core::Filter
{
	Q_OBJECT

	Q_ENUMS(Type)
	Q_PROPERTY(Type type READ type WRITE setType)
	Q_PROPERTY(QDateTime customDateTime READ customDateTime WRITE setCustomDateTime)
	Q_ENUMS(Format)
	Q_PROPERTY(Format format READ format WRITE setFormat)
	Q_PROPERTY(QString customFormat READ customFormat WRITE setCustomFormat)
	Q_PROPERTY(QString separator READ separator WRITE setSeparator)
	Q_ENUMS(InsertionMode)
	Q_PROPERTY(InsertionMode insertionMode READ insertionMode WRITE setInsertionMode)
	Q_PROPERTY(int customInsertionIndex READ customInsertionIndex WRITE setCustomInsertionIndex)

public:
	enum Type {
		LastModificationDate,
		LastAccessDate,
		CreationDate,
		CurrentDate,
		CustomDate
	};

	enum Format {
		DefaultFormat,
		ISOFormat,
		CustomFormat
	};

	enum InsertionMode {
		Prefix,
		Suffix,
		CustomPosition
	};


	DateFilter(QObject *parent = 0);

	QString apply(const core::FilterFileInfo &fileInfo) const;

	QString resume() const;

	Type type() const { return _type; }
	void setType(Type value);

	const QDateTime &customDateTime() const { return _customDateTime; }
	void setCustomDateTime(const QDateTime &value);

	Format format() const { return _format; }
	void setFormat(Format value);

	const QString &customFormat() const { return _customFormat; }
	void setCustomFormat(const QString &value);

	const QString &separator() const { return _separator; }
	void setSeparator(const QString &value);

	InsertionMode insertionMode() const { return _insertionMode; }
	void setInsertionMode(InsertionMode value);

	int customInsertionIndex() const { return _customInsertionIndex; }
	void setCustomInsertionIndex(int value);

private:
	Type _type;
	QDateTime _customDateTime;
	Format _format;
	QString _customFormat;
	QString _separator;
	InsertionMode _insertionMode;
	int _customInsertionIndex;

	static Qt::DateFormat formatToQtDateFormat(Format format);
	static QString typeToString(Type type);
};

#endif
