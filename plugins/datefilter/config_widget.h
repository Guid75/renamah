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
