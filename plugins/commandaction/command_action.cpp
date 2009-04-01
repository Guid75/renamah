#include "process_handler.h"
#include "command_action.h"

void CommandAction::apply(const QString &fileName) const
{
	if (_command == "")
		return;

	QProcess *process = ProcessHandler::instance().createProcess();
	QString program = "/bin/sh";
	QStringList arguments;
	arguments << "-c";
	arguments << QString("%1").arg(_command.arg(fileName));

	process->start(program, arguments);
	process->waitForFinished();
}

QString CommandAction::resume() const
{
	return "$ " + _command;
}

void CommandAction::setCommand(const QString &value)
{
	if (_command == value)
		return;

	_command = value;
	emit settingsChanged();
}

void CommandAction::setDontWaitForEnd(bool value)
{
	if (_dontWaitForEnd == value)
		return;

	_dontWaitForEnd = value;
	emit settingsChanged();
}
