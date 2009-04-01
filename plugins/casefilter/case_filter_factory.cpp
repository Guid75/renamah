#include <QtPlugin>

#include "config_widget.h"
#include "case_filter_factory.h"

CaseFilterFactory::CaseFilterFactory(QObject *parent)
	: QObject(parent) {
}

core::PluginInfo CaseFilterFactory::info() const {
	return core::PluginInfo("case",
							tr("Case"),
							tr("Case manipulations in strings"),
							"Guillaume Denry <guillaume.denry@gmail.com>");
}

core::ModifierConfigWidget *CaseFilterFactory::makeConfigurationWidget(core::Modifier *modifier) const {
     ConfigWidget *widget = new ConfigWidget;
     widget->setModifier(modifier);
     return widget;
}

Q_EXPORT_PLUGIN2(casefilter, CaseFilterFactory)
