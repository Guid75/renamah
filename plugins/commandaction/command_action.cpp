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

	emit settingsChanging();
	_command = value;
	emit settingsChanged();
}

void CommandAction::setDontWaitForEnd(bool value)
{
	if (_dontWaitForEnd == value)
		return;

	emit settingsChanging();
	_dontWaitForEnd = value;
	emit settingsChanged();
}
