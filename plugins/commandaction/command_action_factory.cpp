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
