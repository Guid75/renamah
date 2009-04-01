#ifndef COMMAND_ACTION_FACTORY_H
#define COMMAND_ACTION_FACTORY_H

#include <QObject>
#include <QWidget>

#include <interfaces/action_factory.h>
#include <interfaces/modifier_config_widget.h>

#include "command_action.h"

class CommandActionFactory : public QObject,
                             public core::ActionFactory
{
	Q_OBJECT
	Q_INTERFACES(core::ActionFactory)

public:
	CommandActionFactory(QObject *parent = 0);

	core::PluginInfo info() const;

	core::ModifierConfigWidget *makeConfigurationWidget(core::Modifier *modifier) const;

protected:
	core::Action *createAction() const { return new CommandAction(); }
};

#endif
