#include <QtPlugin>

#include "config_widget.h"
#include "command_action_factory.h"

CommandActionFactory::CommandActionFactory(QObject *parent)
	: QObject(parent) {
}

core::PluginInfo CommandActionFactory::info() const {
	return core::PluginInfo("command",
							tr("Command"),
							tr("Launch a system command for each treated file"),
							"Guillaume Denry <guillaume.denry@gmail.com>");
}

core::ModifierConfigWidget *CommandActionFactory::makeConfigurationWidget(core::Modifier *modifier) const {
	ConfigWidget *widget = new ConfigWidget;
	widget->setModifier(modifier);
	return widget;
}

Q_EXPORT_PLUGIN2(commandaction, CommandActionFactory)
