#include "config_widget.h"

ConfigWidget::ConfigWidget() :
     core::ModifierConfigWidget()
{
     setupUi(this);
}

void ConfigWidget::refreshControls() {
     ReplaceFilter *replaceFilter = static_cast<ReplaceFilter*>(modifier());

     lineEditTarget->setText(replaceFilter->targetPattern());
     lineEditReplacement->setText(replaceFilter->replacement());

	 checkBoxCaseSensitive->setChecked(replaceFilter->caseSensitive());

     switch (replaceFilter->targetPatternSyntax())
     {
     case ReplaceFilter::FixedString:
          radioButtonFixedString->setChecked(true);
          break;
     case ReplaceFilter::RegExp:
          radioButtonRegExp->setChecked(true);
          break;
     case ReplaceFilter::Wildcard:
          radioButtonWildcard->setChecked(true);
          break;
     default:;
     }
}

void ConfigWidget::on_lineEditTarget_textChanged(const QString &text)
{
     ReplaceFilter *replaceFilter = static_cast<ReplaceFilter*>(modifier());
     replaceFilter->setTargetPattern(text);
}

void ConfigWidget::on_lineEditReplacement_textChanged(const QString &text)
{
     ReplaceFilter *replaceFilter = static_cast<ReplaceFilter*>(modifier());
     replaceFilter->setReplacement(text);
}

void ConfigWidget::on_radioButtonFixedString_toggled(bool checked)
{
     if (!checked)
          return;

     ReplaceFilter *replaceFilter = static_cast<ReplaceFilter*>(modifier());
     replaceFilter->setTargetPatternSyntax(ReplaceFilter::FixedString);
}

void ConfigWidget::on_radioButtonRegExp_toggled(bool checked)
{
     if (!checked)
          return;

     ReplaceFilter *replaceFilter = static_cast<ReplaceFilter*>(modifier());
     replaceFilter->setTargetPatternSyntax(ReplaceFilter::RegExp);
}

void ConfigWidget::on_radioButtonWildcard_toggled(bool checked)
{
     if (!checked)
          return;

     ReplaceFilter *replaceFilter = static_cast<ReplaceFilter*>(modifier());
     replaceFilter->setTargetPatternSyntax(ReplaceFilter::Wildcard);
}

void ConfigWidget::on_checkBoxCaseSensitive_toggled(bool checked)
{
     ReplaceFilter *replaceFilter = static_cast<ReplaceFilter*>(modifier());
     replaceFilter->setCaseSensitive(checked);
}

void ConfigWidget::languageChanged() {
	retranslateUi(this);
}
