#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QRadioButton>

#include <interfaces/modifier_config_widget.h>

#include "case_filter.h"

#include "ui_config_widget.h"

class ConfigWidget : public core::ModifierConfigWidget, private Ui::ConfigWidget
{
     Q_OBJECT

public:
	ConfigWidget();

protected:
	void languageChanged();

protected slots:
	void refreshControls();

private:
	QMap<QRadioButton*, CaseFilter::Operation> _radioButton2Operation;

private slots:
	void on_checkBoxDontLowerOtherChars_toggled(bool checked);
	void operationRadioButtonToggled(bool checked);
};

#endif
