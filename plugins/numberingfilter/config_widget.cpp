#include "numbering_filter.h"

#include "config_widget.h"

ConfigWidget::ConfigWidget() :
     core::ModifierConfigWidget() {
     setupUi(this);
}

void ConfigWidget::refreshControls() {
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());

	// Refresh controls
	spinBoxFrom->setValue(filter->start());
	spinBoxStep->setValue(filter->step());

	lineEditSeparator->setText(filter->separator());
	comboBoxType->setCurrentIndex(filter->displayType());
	comboBoxBase->setCurrentIndex(filter->base() - 2);
	spinBoxPadding->setValue(filter->padding());

	switch (filter->insertionMode()) {
	case NumberingFilter::Suffix:
		radioButtonSuffix->setChecked(true);
		break;
	case NumberingFilter::Prefix:
		radioButtonPrefix->setChecked(true);
		break;
	case NumberingFilter::CustomPosition:
		radioButtonCustomPosition->setChecked(true);
		spinBoxCustomPosition->setValue(filter->customInsertionIndex());
		break;
	}
}

void ConfigWidget::on_spinBoxFrom_valueChanged(int value) {
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setStart(value);
}

void ConfigWidget::on_spinBoxStep_valueChanged(int value) {
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setStep(value);
}

void ConfigWidget::on_radioButtonPrefix_toggled(bool checked) {
	if (!checked)
		return;

	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setInsertionMode(NumberingFilter::Prefix);
	spinBoxCustomPosition->setEnabled(false);
}

void ConfigWidget::on_radioButtonSuffix_toggled(bool checked) {
	if (!checked)
		return;

	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setInsertionMode(NumberingFilter::Suffix);
	spinBoxCustomPosition->setEnabled(false);
}

void ConfigWidget::on_radioButtonCustomPosition_toggled(bool checked) {
	if (!checked)
		return;

	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setInsertionMode(NumberingFilter::CustomPosition);
	spinBoxCustomPosition->setEnabled(true);
}

void ConfigWidget::on_spinBoxCustomPosition_valueChanged(int value) {
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setCustomInsertionIndex(value);
}

void ConfigWidget::on_lineEditSeparator_textChanged(const QString &text) {
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setSeparator(text);
}

void ConfigWidget::on_comboBoxBase_currentIndexChanged(int index) {
	if (isLanguageChanging())
		return;
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setBase(index + 2);
}

void ConfigWidget::on_spinBoxPadding_valueChanged(int value) {
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setPadding(value);
}

void ConfigWidget::on_comboBoxType_currentIndexChanged(int index) {
	if (isLanguageChanging())
		return;
	NumberingFilter *filter = static_cast<NumberingFilter*>(modifier());
	filter->setDisplayType((NumberingFilter::DisplayType) index);
	comboBoxBase->setEnabled(!index);
}

void ConfigWidget::languageChanged() {
	int oldBaseIndex = comboBoxBase->currentIndex();
	int oldTypeIndex = comboBoxType->currentIndex();

	retranslateUi(this);

	comboBoxType->setCurrentIndex(oldTypeIndex);
	comboBoxBase->setCurrentIndex(oldBaseIndex);
}
