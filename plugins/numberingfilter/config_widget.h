#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <interfaces/modifier_config_widget.h>

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

private slots:
	void on_spinBoxFrom_valueChanged(int value);
	void on_spinBoxStep_valueChanged(int value);
	void on_radioButtonPrefix_toggled(bool checked);
	void on_radioButtonSuffix_toggled(bool checked);
	void on_radioButtonCustomPosition_toggled(bool checked);
	void on_spinBoxCustomPosition_valueChanged(int value);
	void on_lineEditSeparator_textChanged(const QString &text);
	void on_comboBoxBase_currentIndexChanged(int index);
	void on_spinBoxPadding_valueChanged(int value);
	void on_comboBoxType_currentIndexChanged(int index);
};

#endif
