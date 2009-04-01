#include <QtPlugin>

#include "config_widget.h"
#include "cutter_filter_factory.h"

CutterFilterFactory::CutterFilterFactory(QObject *parent)
	: QObject(parent) {
}

core::PluginInfo CutterFilterFactory::info() const {
	return core::PluginInfo("cutter",
							tr("Cutter"),
							tr("Cut some parts of files"),
							"Guillaume Denry <guillaume.denry@gmail.com>");
}

core::ModifierConfigWidget *CutterFilterFactory::makeConfigurationWidget(core::Modifier *modifier) const {
     ConfigWidget *widget = new ConfigWidget;
     widget->setModifier(modifier);
     return widget;
}

Q_EXPORT_PLUGIN2(cutterfilter, CutterFilterFactory)
