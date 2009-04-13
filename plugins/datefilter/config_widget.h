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

#include <QDialog>

#include <interfaces/modifier_config_widget.h>

#include "date_filter.h"
#include "ui_config_widget.h"

class ConfigWidget : public core::ModifierConfigWidget, private Ui::ConfigWidget
{
     Q_OBJECT

public:
	ConfigWidget();

protected:
	void languageChanged();
	bool eventFilter(QObject *watched, QEvent *event);

protected slots:
	void refreshControls();

private:
	QDialog *_helpDialog;
	DateFilter *filter() { return static_cast<DateFilter*>(modifier()); }

private slots:
	void on_comboBoxDate_currentIndexChanged(int index);
	void on_dateTimeEditCustom_dateTimeChanged(const QDateTime &dateTime);
	void on_radioButtonPrefix_toggled(bool checked);
	void on_radioButtonSuffix_toggled(bool checked);
	void on_radioButtonCustomPosition_toggled(bool checked);
	void on_lineEditSeparator_textChanged(const QString &text);
	void on_spinBoxCustomPosition_valueChanged(int value);
	void on_comboBoxFormat_currentIndexChanged(int index);
	void on_comboBoxCustomFormat_editTextChanged(const QString &text);
	void on_toolButtonFormatHelp_clicked();
};

#endif
