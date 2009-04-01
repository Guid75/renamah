#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QThread>
#include <QPair>

class Processor : public QThread
{
	Q_OBJECT

public:
	enum DestinationOperation {
		Rename,
		Copy,
		Move,
		SymLink
	};

	static Processor &instance();

	void clearTasks();
	void addTask(const QString &oldFileName, const QString &newFileName);
	bool hasTasks() const { return tasks.count(); }

	DestinationOperation destinationOperation() const { return _destinationOperation; }
	void setDestinationOperation(DestinationOperation operation);
	QString destinationOperationName() const;
	const QString &destinationDir() const { return _destinationDir; }
	void setDestinationDir(const QString &dir);

	void go();

signals:
	void taskSuccess(const QString &original, const QString &renamed);
	void taskFailure(const QString &original, const QString &renamed, const QString &errorMsg);
	void percentProgress(int percent);

protected:
	void run();

private:
	static Processor *_instance;
	QList<QPair<QString,QString> > tasks;
//	QList<QPair<QString,QString> > failed;
//	QList<QPair<QString,QString> > succeed;
	int _lastPercent;
	DestinationOperation _destinationOperation;
	QString _destinationDir;

	Processor(QObject *parent = 0);
};

#endif
