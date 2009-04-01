#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <interfaces/modifier_config_widget.h>

#include "command_action.h"

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
	void on_lineEditCommand_textChanged(const QString &text);
};

#endif
