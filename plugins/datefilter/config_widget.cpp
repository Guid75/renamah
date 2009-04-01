#include "config_widget.h"
#include "ui_help_widget.h"

ConfigWidget::ConfigWidget()
	: core::ModifierConfigWidget(),
	  _helpDialog(0) {
	setupUi(this);
}

void ConfigWidget::refreshControls() {
	DateFilter *filter = this->filter();

	// Refresh controls
	comboBoxDate->setCurrentIndex(filter->type());
	dateTimeEditCustom->setDateTime(filter->customDateTime());
	dateTimeEditCustom->setEnabled(filter->type() == DateFilter::CustomDate);

	lineEditSeparator->setText(filter->separator());

	comboBoxFormat->setCurrentIndex(filter->format());
	comboBoxCustomFormat->setEditText(filter->customFormat());
	comboBoxCustomFormat->setEnabled(filter->format() == DateFilter::CustomFormat);

	switch (filter->insertionMode()) {
	case DateFilter::Suffix:
		radioButtonSuffix->setChecked(true);
		break;
	case DateFilter::Prefix:
		radioButtonPrefix->setChecked(true);
		break;
	case DateFilter::CustomPosition:
		radioButtonCustomPosition->setChecked(true);
		spinBoxCustomPosition->setValue(filter->customInsertionIndex());
		break;
	}
}

void ConfigWidget::languageChanged() {
	int oldComboBoxDateIndex = comboBoxDate->currentIndex();
	int oldComboBoxFormatIndex = comboBoxFormat->currentIndex();

	retranslateUi(this);

	comboBoxDate->setCurrentIndex(oldComboBoxDateIndex);
	comboBoxFormat->setCurrentIndex(oldComboBoxFormatIndex);
}

void ConfigWidget::on_comboBoxDate_currentIndexChanged(int index) {
	if (isLanguageChanging())
		return;

	filter()->setType((DateFilter::Type) index);
}

void ConfigWidget::on_dateTimeEditCustom_dateTimeChanged(const QDateTime &dateTime) {
	filter()->setCustomDateTime(dateTime);
}

void ConfigWidget::on_radioButtonPrefix_toggled(bool checked) {
	if (!checked)
		return;

	filter()->setInsertionMode(DateFilter::Prefix);
	spinBoxCustomPosition->setEnabled(false);
}

void ConfigWidget::on_radioButtonSuffix_toggled(bool checked) {
	if (!checked)
		return;

	filter()->setInsertionMode(DateFilter::Suffix);
	spinBoxCustomPosition->setEnabled(false);
}

void ConfigWidget::on_radioButtonCustomPosition_toggled(bool checked) {
	if (!checked)
		return;

	filter()->setInsertionMode(DateFilter::CustomPosition);
	spinBoxCustomPosition->setEnabled(true);
}

void ConfigWidget::on_lineEditSeparator_textChanged(const QString &text) {
	filter()->setSeparator(text);
}

void ConfigWidget::on_spinBoxCustomPosition_valueChanged(int value) {
	filter()->setCustomInsertionIndex(value);
}

void ConfigWidget::on_comboBoxFormat_currentIndexChanged(int index) {
	if (isLanguageChanging())
		return;

	filter()->setFormat((DateFilter::Format) index);
}

void ConfigWidget::on_comboBoxCustomFormat_editTextChanged(const QString &text) {
	if (isLanguageChanging())
		return;

	filter()->setCustomFormat(text);
}

void ConfigWidget::on_toolButtonFormatHelp_clicked() {
	if (_helpDialog) {
		delete _helpDialog;
		_helpDialog = 0;
		return;
	}
	_helpDialog = new QDialog(this, Qt::WindowStaysOnTopHint);
	_helpDialog->setAttribute(Qt::WA_DeleteOnClose, true);
	_helpDialog->installEventFilter(this);
	Ui::HelpWidget ui;
	ui.setupUi(_helpDialog);
	_helpDialog->show();
}

bool ConfigWidget::eventFilter(QObject *watched, QEvent *event) {
	if (watched == _helpDialog && event->type() == QEvent::Close)
		_helpDialog = 0;
	return core::ModifierConfigWidget::eventFilter(watched, event);
}
