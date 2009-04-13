/*
 * Renamah
 * Copyright (C) 2009 Guillaume Denry <guillaume.denry@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
