#ifndef CASE_FILTER_FACTORY_H
#define CASE_FILTER_FACTORY_H

#include <QObject>
#include <QWidget>

#include <interfaces/filter_factory.h>
#include <interfaces/modifier_config_widget.h>

#include "case_filter.h"

class CaseFilterFactory : public QObject,
						  public core::FilterFactory
{
	Q_OBJECT
	Q_INTERFACES(core::FilterFactory)

public:
	CaseFilterFactory(QObject *parent = 0);

	core::PluginInfo info() const;

	core::Modifier *makeModifier() const;

	core::ModifierConfigWidget *makeConfigurationWidget(core::Modifier *modifier) const;

protected:
	core::Filter *createFilter() const { return new CaseFilter(); }
};

#endif
