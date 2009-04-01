#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <interfaces/modifier_config_widget.h>

#include "replace_filter.h"

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
	void on_lineEditTarget_textChanged(const QString &text);
	void on_lineEditReplacement_textChanged(const QString &text);
	void on_checkBoxCaseSensitive_toggled(bool checked);
	void on_radioButtonFixedString_toggled(bool checked);
	void on_radioButtonRegExp_toggled(bool checked);
	void on_radioButtonWildcard_toggled(bool checked);
};

#endif
