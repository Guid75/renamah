#ifndef REPLACE_FILTER_FACTORY_H
#define REPLACE_FILTER_FACTORY_H

#include <QObject>
#include <QWidget>

#include <interfaces/filter_factory.h>
#include <interfaces/modifier_config_widget.h>

#include "replace_filter.h"

class ReplaceFilterFactory : public QObject,
                             public core::FilterFactory
{
	Q_OBJECT
	Q_INTERFACES(core::FilterFactory)

public:
	ReplaceFilterFactory(QObject *parent = 0);

	core::PluginInfo info() const;

	core::ModifierConfigWidget *makeConfigurationWidget(core::Modifier *modifier) const;

protected:
	core::Filter *createFilter() const { return new ReplaceFilter(); }
};

#endif
