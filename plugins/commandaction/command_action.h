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

#ifndef COMMAND_ACTION_H
#define COMMAND_ACTION_H

#include <QObject>
#include <QRegExp>

#include <interfaces/action.h>

class CommandAction : public core::Action
{
	Q_OBJECT

public:
	CommandAction(QObject *parent = 0)
		: core::Action(parent) {}

	void apply(const QString &fileName) const;

	QString resume() const;

	const QString &command() const { return _command; }
	void setCommand(const QString &value);

	bool dontWaitForEnd() const { return _dontWaitForEnd; }
	void setDontWaitForEnd(bool value);

private:
	QString _command;
	bool _dontWaitForEnd;
};

#endif
