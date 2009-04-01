#ifndef PROCESS_HANDLER_H
#define PROCESS_HANDLER_H

#include <QObject>
#include <QProcess>

class ProcessHandler : public QObject
{
	Q_OBJECT

public:
	static ProcessHandler &instance();

	QProcess *createProcess();

private:
	static ProcessHandler *_instance;

private slots:
	void processError(QProcess::ProcessError error);
	void processStarted();
	void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif
