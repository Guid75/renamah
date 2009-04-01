#ifndef CUTTER_FILTER_FACTORY_H
#define CUTTER_FILTER_FACTORY_H

#include <QWidget>

#include <interfaces/filter_factory.h>
#include <interfaces/modifier_config_widget.h>

#include "cutter_filter.h"

class CutterFilterFactory : public QObject,
							public core::FilterFactory
{
	Q_OBJECT
	Q_INTERFACES(core::FilterFactory)

public:
	CutterFilterFactory(QObject *parent = 0);

	core::PluginInfo info() const;

	core::ModifierConfigWidget *makeConfigurationWidget(core::Modifier *modifier) const;

protected:
	core::Filter *createFilter() const { return new CutterFilter(); }
};

#endif
