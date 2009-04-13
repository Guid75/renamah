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

#include "widget_actions.h"

WidgetActions::WidgetActions(QWidget *parent)
	: WidgetModifiers(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(widgetConfig);
	mainLayout->setMargin(0);

	// Constructs actions specific widgets
	scrollAreaGeneral = new QScrollArea;
	scrollAreaGeneral->setFrameShape(QFrame::NoFrame);
	scrollAreaGeneral->setWidgetResizable(true);
	mainLayout->addWidget(scrollAreaGeneral);
}

void WidgetActions::setConfigWidget(QWidget *widget)
{
	scrollAreaGeneral->setWidget(widget);
}
