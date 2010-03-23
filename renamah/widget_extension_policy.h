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

#ifndef WIDGET_EXTENSION_POLICY_H
#define WIDGET_EXTENSION_POLICY_H

#include "extension_policy.h"

#include "ui_widget_extension_policy.h"

class WidgetExtensionPolicy : public QWidget, private Ui::WidgetExtensionPolicy
{
    Q_OBJECT

public:
    WidgetExtensionPolicy(QWidget *parent = 0);

    const ExtensionPolicy &extensionPolicy() const { return _extensionPolicy; }
    void setExtensionPolicy(const ExtensionPolicy &policy);

signals:
    void extensionPolicyChanged();

protected:
    void changeEvent(QEvent *event);

private:
    ExtensionPolicy _extensionPolicy;

    void refreshControls();

private slots:
    void on_radioButtonFilterBasename_toggled(bool checked);
    void on_radioButtonFilterAll_toggled(bool checked);
    void on_radioButtonFilterExtension_toggled(bool checked);
    void on_radioButtonExtensionDefinitionLastPoint_toggled(bool checked);
    void on_radioButtonExtensionDefinitionFirstPoint_toggled(bool checked);
    void on_radioButtonExtensionDefinitionNthPoint_toggled(bool checked);
    void on_spinBoxExtensionNthPoint_valueChanged(int value);
    void on_pushButtonReset_clicked();
};

#endif
