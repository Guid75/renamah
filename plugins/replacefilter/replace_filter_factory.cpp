#include <QtPlugin>

#include "config_widget.h"
#include "replace_filter_factory.h"

ReplaceFilterFactory::ReplaceFilterFactory(QObject *parent)
	: QObject(parent) {
}

core::PluginInfo ReplaceFilterFactory::info() const {
	return core::PluginInfo("replace",
							tr("Replacement"),
							tr("Replace pieces in strings"),
							"Guillaume Denry <guillaume.denry@gmail.com>");
}

core::ModifierConfigWidget *ReplaceFilterFactory::makeConfigurationWidget(core::Modifier *modifier) const {
     ConfigWidget *widget = new ConfigWidget;
     widget->setModifier(modifier);
     return widget;
}

Q_EXPORT_PLUGIN2(replacefilter, ReplaceFilterFactory)
