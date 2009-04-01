#include <QtPlugin>

#include "config_widget.h"
#include "date_filter_factory.h"

DateFilterFactory::DateFilterFactory(QObject *parent)
	: QObject(parent) {
}

core::PluginInfo DateFilterFactory::info() const {
	return core::PluginInfo("date",
							tr("Date"),
							tr("Add date in file names"),
							"Guillaume Denry <guillaume.denry@gmail.com>");
}

core::ModifierConfigWidget *DateFilterFactory::makeConfigurationWidget(core::Modifier *modifier) const {
     ConfigWidget *widget = new ConfigWidget;
     widget->setModifier(modifier);
     return widget;
}

Q_EXPORT_PLUGIN2(datefilter, DateFilterFactory)
