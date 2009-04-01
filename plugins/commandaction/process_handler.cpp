#include "process_handler.h"

ProcessHandler *ProcessHandler::_instance = 0;

ProcessHandler &ProcessHandler::instance()
{
	if (!_instance)
		_instance = new ProcessHandler;

	return *_instance;
}

QProcess *ProcessHandler::createProcess()
{
	QProcess *process = new QProcess(this);

	connect(process, SIGNAL(error(QProcess::ProcessError)),
			this, SLOT(processError(QProcess::ProcessError)));
	connect(process, SIGNAL(started()),
			this, SLOT(processStarted()));
	connect(process, SIGNAL(finished(int, QProcess::ExitStatus)),
			this, SLOT(processFinished(int, QProcess::ExitStatus)));

	return process;
}

void ProcessHandler::processError(QProcess::ProcessError error)
{
}

void ProcessHandler::processStarted()
{
}

void ProcessHandler::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
}
