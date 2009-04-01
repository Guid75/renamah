#include <QFile>
#include <QDir>
#include <QFileInfo>

#include "file_model.h"
#include "filter_model.h"
#include "finalizer_model.h"
#include "processor.h"

Processor *Processor::_instance = 0;

Processor &Processor::instance()
{
	if (!_instance)
		_instance = new Processor;

	return *_instance;
}

Processor::Processor(QObject *parent)
	: QThread(parent),
	  _destinationOperation(Rename)
{
}

void Processor::run()
{
	_lastPercent = 0;
	emit percentProgress(_lastPercent);
	typedef QPair<QString,QString> Task;
	int i = 1;
	for (int row = 0; row < FileModel::instance().rowCount(); ++row)
	{
		QString originalFileName = FileModel::instance().originalFileName(FileModel::instance().index(row, 0));
		QString renamedFileName = FileModel::instance().renamedFileName(FileModel::instance().index(row, 0));
//		QString newFileName = FilterModel::instance()->apply(originalFileName);

		QFile file(originalFileName);

		bool result = false;
		QString destinationFileName = QDir(_destinationDir).filePath(QFileInfo(renamedFileName).fileName());

		switch (_destinationOperation)
		{
		case Rename:
			result = file.rename(renamedFileName);
			destinationFileName = renamedFileName;
			break;
		case Copy:
			result = file.copy(destinationFileName);
			break;
		case Move:
			result = file.rename(destinationFileName);
			break;
		case SymLink:
			result = file.link(destinationFileName);
			break;
		default:;
		}

		if (result)
		{
			emit taskSuccess(originalFileName, destinationFileName);
//			succeed << QPair<QString,QString>(task.first, task.second);
		}
		else
		{
			emit taskFailure(originalFileName, destinationFileName, file.errorString());
//			failed << QPair<QString,QString>(task.first, task.second);
		}

		if (result)
			FinalizerModel::instance().apply(destinationFileName);

		int percent = (i * 100) / tasks.count();
		if (percent != _lastPercent)
		{
			_lastPercent = percent;
			emit percentProgress(_lastPercent);
		}
		i++;
	}
}

void Processor::addTask(const QString &oldFileName, const QString &newFileName)
{
	if (isRunning()) // cannot add tasks while running
		return;

	tasks << QPair<QString,QString>(oldFileName, newFileName);
}

void Processor::clearTasks()
{
	if (isRunning()) // cannot clear tasks while running
		return;

	tasks.clear();
}

void Processor::go()
{
	if (!isRunning())
		start();
}

void Processor::setDestinationOperation(DestinationOperation operation)
{
	if (isRunning() || operation == _destinationOperation)
		return;

	_destinationOperation = operation;
}

void Processor::setDestinationDir(const QString &dir)
{
	if (isRunning() || dir == _destinationDir)
		return;

	_destinationDir = dir;
}

QString Processor::destinationOperationName() const
{
	switch (_destinationOperation)
	{
	case Rename: return tr("Rename");
	case Copy: return tr("Copy");
	case Move: return tr("Move");
	case SymLink: return tr("Create link");
	default: return "";
	}
}
