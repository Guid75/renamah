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
