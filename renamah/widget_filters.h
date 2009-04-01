#ifndef WIDGET_FILTERS_H
#define WIDGET_FILTERS_H

#include <QTabWidget>
#include <QScrollArea>
#include <QCheckBox>

#include "widget_modifiers.h"
#include "widget_extension_policy.h"

class WidgetFilters : public WidgetModifiers
{
	Q_OBJECT

public:
	WidgetFilters(QWidget *parent = 0);

	void init(ModifierManager *modifierManager, ModifierModel &modifierModel);

protected:
	void setConfigWidget(QWidget *widget);
	void currentModifierChanged(core::Modifier *modifier);
	void changeEvent(QEvent *event);

private:
	QTabWidget *tabWidgetMain;
	QScrollArea *scrollAreaGeneral;
	QScrollArea *scrollAreaExtensionPolicy;
	QCheckBox *checkBoxExtensionPolicyState;

	WidgetExtensionPolicy *widgetExtensionPolicy;

	void retranslate();

private slots:
	void extensionPolicyStateToggled(bool checked);
	void extensionPolicyChanged();
};

#endif
