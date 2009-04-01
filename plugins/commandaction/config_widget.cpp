#include "config_widget.h"

ConfigWidget::ConfigWidget() :
     core::ModifierConfigWidget()
{
     setupUi(this);
}

void ConfigWidget::refreshControls()
{
     CommandAction *action = static_cast<CommandAction*>(modifier());

     // Refresh controls
	 lineEditCommand->setText(action->command());
	 checkBoxDontWait->setChecked(action->dontWaitForEnd());
}

void ConfigWidget::on_lineEditCommand_textChanged(const QString &text)
{
     CommandAction *commandAction = static_cast<CommandAction*>(modifier());
	 commandAction->setCommand(text);
}

void ConfigWidget::languageChanged() {
	retranslateUi(this);
}
