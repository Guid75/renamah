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

#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <interfaces/modifier_config_widget.h>

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
	void on_spinBoxFrom_valueChanged(int value);
	void on_spinBoxStep_valueChanged(int value);
	void on_radioButtonPrefix_toggled(bool checked);
	void on_radioButtonSuffix_toggled(bool checked);
	void on_radioButtonCustomPosition_toggled(bool checked);
	void on_spinBoxCustomPosition_valueChanged(int value);
	void on_lineEditSeparator_textChanged(const QString &text);
	void on_comboBoxBase_currentIndexChanged(int index);
	void on_spinBoxPadding_valueChanged(int value);
	void on_comboBoxType_currentIndexChanged(int index);
};

#endif
