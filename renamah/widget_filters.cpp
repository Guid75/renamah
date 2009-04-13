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

#include "filter_model.h"
#include "widget_filters.h"

WidgetFilters::WidgetFilters(QWidget *parent)
	: WidgetModifiers(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(widgetConfig);
	mainLayout->setMargin(0);

	// Constructs filters specific widgets
	tabWidgetMain = new QTabWidget;
	mainLayout->addWidget(tabWidgetMain);

	scrollAreaGeneral = new QScrollArea;
	scrollAreaGeneral->setFrameShape(QFrame::NoFrame);
 	scrollAreaGeneral->setWidgetResizable(true);
	tabWidgetMain->addTab(scrollAreaGeneral, "");

	scrollAreaExtensionPolicy = new QScrollArea;
	scrollAreaExtensionPolicy->setFrameShape(QFrame::NoFrame);
	scrollAreaExtensionPolicy->setWidgetResizable(true);
	tabWidgetMain->addTab(scrollAreaExtensionPolicy, "");
	QWidget *widget = new QWidget;
	QVBoxLayout *layout = new QVBoxLayout(widget);
	scrollAreaExtensionPolicy->setWidget(widget);
	checkBoxExtensionPolicyState = new QCheckBox;
	connect(checkBoxExtensionPolicyState, SIGNAL(toggled(bool)),
			this, SLOT(extensionPolicyStateToggled(bool)));
	layout->addWidget(checkBoxExtensionPolicyState);
	layout->addWidget(widgetExtensionPolicy = new WidgetExtensionPolicy);
	connect(widgetExtensionPolicy, SIGNAL(extensionPolicyChanged()),
			this, SLOT(extensionPolicyChanged()));

	retranslate();
}

void WidgetFilters::retranslate() {
	checkBoxExtensionPolicyState->setText(tr("Override the global extension policy"));
	tabWidgetMain->setTabText(tabWidgetMain->indexOf(scrollAreaGeneral), tr("General"));
	tabWidgetMain->setTabText(tabWidgetMain->indexOf(scrollAreaExtensionPolicy), tr("Extension policy"));
}

void WidgetFilters::extensionPolicyStateToggled(bool checked)
{
	widgetExtensionPolicy->setEnabled(checked);
	core::Filter *filter = static_cast<core::Filter*>(currentModifier());
	FilterModel::instance().setLocalExtensionPolicyEnabled(filter, checked);
}

void WidgetFilters::setConfigWidget(QWidget *widget)
{
	scrollAreaGeneral->setWidget(widget);
}

void WidgetFilters::init(ModifierManager *modifierManager, ModifierModel &modifierModel)
{
	WidgetModifiers::init(modifierManager, modifierModel);

	tabWidgetMain->setCurrentWidget(scrollAreaGeneral);
	widgetExtensionPolicy->setEnabled(false);
}

void WidgetFilters::currentModifierChanged(core::Modifier *modifier)
{
	core::Filter *filter = static_cast<core::Filter*>(modifier);
	checkBoxExtensionPolicyState->setChecked(FilterModel::instance().isLocalExtensionPolicyEnabled(filter));
	widgetExtensionPolicy->setExtensionPolicy(FilterModel::instance().localExtensionPolicy(filter));
}

void WidgetFilters::extensionPolicyChanged()
{
	core::Filter *filter = static_cast<core::Filter*>(currentModifier());
	FilterModel::instance().setLocalExtensionPolicy(filter, widgetExtensionPolicy->extensionPolicy());
}

void WidgetFilters::changeEvent(QEvent *event) {
	if (event->type() == QEvent::LanguageChange)
		retranslate();
	WidgetModifiers::changeEvent(event);
}
