#ifndef NUMBERING_FILTER_FACTORY_H
#define NUMBERING_FILTER_FACTORY_H

#include <QWidget>

#include <interfaces/filter_factory.h>
#include <interfaces/modifier_config_widget.h>

#include "numbering_filter.h"

class NumberingFilterFactory : public QObject,
							   public core::FilterFactory
{
	Q_OBJECT
	Q_INTERFACES(core::FilterFactory)

public:
	NumberingFilterFactory(QObject *parent = 0);

	core::PluginInfo info() const;

	core::ModifierConfigWidget *makeConfigurationWidget(core::Modifier *modifier) const;

protected:
	core::Filter *createFilter() const { return new NumberingFilter(); }
};

#endif
