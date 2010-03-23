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

#ifndef WIDGET_FILTERS_H
#define WIDGET_FILTERS_H

#include <QTabWidget>
#include <QScrollArea>
#include <QCheckBox>

#include "widget_modifiers.h"
#include "widget_extension_policy.h"

class WidgetFilters : public WidgetModifiers
{
    Q_OBJECT

public:
    WidgetFilters(QWidget *parent = 0);

    void init(ModifierManager *modifierManager, ModifierModel &modifierModel);

protected:
    void setConfigWidget(QWidget *widget);
    void currentModifierChanged(core::Modifier *modifier);
    void changeEvent(QEvent *event);

private:
    QTabWidget *tabWidgetMain;
    QScrollArea *scrollAreaGeneral;
    QScrollArea *scrollAreaExtensionPolicy;
    QCheckBox *checkBoxExtensionPolicyState;

    WidgetExtensionPolicy *widgetExtensionPolicy;

    void retranslate();

private slots:
    void extensionPolicyStateToggled(bool checked);
    void extensionPolicyChanged();
};

#endif
