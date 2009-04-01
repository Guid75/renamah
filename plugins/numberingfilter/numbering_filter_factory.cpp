#include <QtPlugin>

#include "config_widget.h"
#include "numbering_filter_factory.h"

NumberingFilterFactory::NumberingFilterFactory(QObject *parent)
	: QObject(parent) {
}

core::PluginInfo NumberingFilterFactory::info() const {
	return core::PluginInfo("numbering",
							tr("Numbering"),
							tr("Add a numbering to files"),
							"Guillaume Denry <guillaume.denry@gmail.com>");
}

core::ModifierConfigWidget *NumberingFilterFactory::makeConfigurationWidget(core::Modifier *modifier) const {
     ConfigWidget *widget = new ConfigWidget;
     widget->setModifier(modifier);
     return widget;
}

Q_EXPORT_PLUGIN2(numberingfilter, NumberingFilterFactory)
