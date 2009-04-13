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

#include <QMessageBox>

#include "widget_extension_policy.h"

WidgetExtensionPolicy::WidgetExtensionPolicy(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	refreshControls();
}

void WidgetExtensionPolicy::setExtensionPolicy(const ExtensionPolicy &policy)
{
	if (policy == _extensionPolicy)
		return;

	_extensionPolicy = policy;

	refreshControls();
}

void WidgetExtensionPolicy::refreshControls()
{
	switch (_extensionPolicy.filterPolicy())
	{
	case ExtensionPolicy::FilterBaseName:
		radioButtonFilterBasename->setChecked(true);
		break;
	case ExtensionPolicy::FilterExtension:
		radioButtonFilterExtension->setChecked(true);
		break;
	case ExtensionPolicy::FilterAll:
		radioButtonFilterAll->setChecked(true);
		break;
	default:;
	}

	switch (_extensionPolicy.extensionDefinition())
	{
	case ExtensionPolicy::FirstPoint:
		radioButtonExtensionDefinitionFirstPoint->setChecked(true);
		break;
	case ExtensionPolicy::LastPoint:
		radioButtonExtensionDefinitionLastPoint->setChecked(true);
		break;
	case ExtensionPolicy::NthPointFromRight:
		radioButtonExtensionDefinitionNthPoint->setChecked(true);
		break;
	default:;
	}

	spinBoxExtensionNthPoint->setEnabled(radioButtonExtensionDefinitionNthPoint->isChecked());
	spinBoxExtensionNthPoint->setValue(_extensionPolicy.nthPointFromRight());
	labelExtensionNthPoint->setEnabled(radioButtonExtensionDefinitionNthPoint->isChecked());
}

void WidgetExtensionPolicy::on_radioButtonFilterBasename_toggled(bool checked)
{
	if (checked)
	{
		_extensionPolicy.setFilterPolicy(ExtensionPolicy::FilterBaseName);
		emit extensionPolicyChanged();
	}
}

void WidgetExtensionPolicy::on_radioButtonFilterAll_toggled(bool checked)
{
	if (checked)
	{
		_extensionPolicy.setFilterPolicy(ExtensionPolicy::FilterAll);
		emit extensionPolicyChanged();
	}
}

void WidgetExtensionPolicy::on_radioButtonFilterExtension_toggled(bool checked)
{
	if (checked)
	{
		_extensionPolicy.setFilterPolicy(ExtensionPolicy::FilterExtension);
		emit extensionPolicyChanged();
	}
}

void WidgetExtensionPolicy::on_radioButtonExtensionDefinitionLastPoint_toggled(bool checked)
{
	if (checked)
	{
		_extensionPolicy.setExtensionDefinition(ExtensionPolicy::LastPoint);
		emit extensionPolicyChanged();
	}
}

void WidgetExtensionPolicy::on_radioButtonExtensionDefinitionFirstPoint_toggled(bool checked)
{
	if (checked)
	{
		_extensionPolicy.setExtensionDefinition(ExtensionPolicy::FirstPoint);
		emit extensionPolicyChanged();
	}
}

void WidgetExtensionPolicy::on_radioButtonExtensionDefinitionNthPoint_toggled(bool checked)
{
	spinBoxExtensionNthPoint->setEnabled(checked);
	labelExtensionNthPoint->setEnabled(checked);

	if (checked)
	{
		_extensionPolicy.setExtensionDefinition(ExtensionPolicy::NthPointFromRight);
		emit extensionPolicyChanged();
	}
}

void WidgetExtensionPolicy::on_spinBoxExtensionNthPoint_valueChanged(int value)
{
	_extensionPolicy.setNthPointFromRight(value);
	emit extensionPolicyChanged();
}

void WidgetExtensionPolicy::on_pushButtonReset_clicked()
{
	if (QMessageBox::question(this, tr("Are you sure?"), tr("Do you really want to return to default extension policy settings?"),
							  QMessageBox::Yes | QMessageBox::Cancel) != QMessageBox::Yes)
		return;

	_extensionPolicy.reset();
	refreshControls();
	emit extensionPolicyChanged();
}

void WidgetExtensionPolicy::changeEvent(QEvent *event) {
	if (event->type() == QEvent::LanguageChange) {
		retranslateUi(this);
	} else
		QWidget::changeEvent(event);
}
