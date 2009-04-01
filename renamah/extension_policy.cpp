#include "extension_policy.h"

QString ExtensionPolicy::applyFilterOnFilePath(const core::Filter &filter, int fileIndex, const QString &filePath,
	const QString &originalFilePath) const
{
	QDir dir = QFileInfo(filePath).dir();

	if (_filterPolicy == FilterAll)
		return dir.filePath(filter.apply(core::FilterFileInfo(originalFilePath, QFileInfo(filePath).fileName(), fileIndex)));

	QString baseName, extension;
	getBaseNameAndExtension(filePath, baseName, extension);

	switch (_filterPolicy)
	{
	case FilterBaseName: return getFilePath(filter.apply(core::FilterFileInfo(originalFilePath, baseName, fileIndex)), extension, dir);
	case FilterExtension: return getFilePath(baseName, filter.apply(core::FilterFileInfo(originalFilePath, extension, fileIndex)), dir);
	default: return "";
	}
}

void ExtensionPolicy::getBaseNameAndExtension(const QString &filePath, QString &baseName, QString &extension) const
{
	QFileInfo fileInfo(filePath);

	switch (_extensionDefinition)
	{
	case LastPoint:
		baseName = fileInfo.completeBaseName();
		extension = fileInfo.suffix();
		break;
	case FirstPoint:
		baseName = fileInfo.baseName();
		extension = fileInfo.completeSuffix();
		break;
	case NthPointFromRight:
	{
		QString fileName = fileInfo.fileName();
		int point = qMin(_nthPointFromRight + 1, fileName.count('.') + 1);
		baseName = fileName.section('.', 0, - point);
		extension = fileName.section('.', - point + 1, -1);
		break;
	}
	default:;
	}
}

QString ExtensionPolicy::getFilePath(const QString &baseName, const QString &extension, const QDir &dir) const
{
	if (extension == "")
		return dir.absoluteFilePath(baseName);
	else
		return dir.absoluteFilePath(baseName + "." + extension);
}

void ExtensionPolicy::reset()
{
	*this = ExtensionPolicy();
}
