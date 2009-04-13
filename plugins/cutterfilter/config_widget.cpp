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

#include "config_widget.h"

ConfigWidget::ConfigWidget()
	: core::ModifierConfigWidget() {
	setupUi(this);
}

void ConfigWidget::refreshControls() {
	CutterFilter *filter = this->filter();

	// Refresh controls
	spinBoxStartMarker->setValue(filter->startMarkerIndex());
	comboBoxStartMarkerPosition->setCurrentIndex(filter->startMarkerPosition());

	spinBoxEndMarker->setValue(filter->endMarkerIndex());
	comboBoxEndMarkerPosition->setCurrentIndex(filter->endMarkerPosition());

	if (filter->operation() == CutterFilter::Keep)
		radioButtonKeep->setChecked(true);
	else
		radioButtonRemove->setChecked(true);
}

void ConfigWidget::on_spinBoxStartMarker_valueChanged(int value) {
	filter()->setStartMarkerIndex(value, true);
}

void ConfigWidget::on_comboBoxStartMarkerPosition_currentIndexChanged(int index) {
	if (isLanguageChanging())
		return;

	filter()->setStartMarkerPosition((CutterFilter::Position) index, true);
}

void ConfigWidget::on_spinBoxEndMarker_valueChanged(int value) {
	filter()->setEndMarkerIndex(value, true);
}

void ConfigWidget::on_comboBoxEndMarkerPosition_currentIndexChanged(int index) {
	if (isLanguageChanging())
		return;

	filter()->setEndMarkerPosition((CutterFilter::Position) index, true);
}

void ConfigWidget::on_radioButtonKeep_toggled(bool checked) {
	if (!checked)
		return;

	filter()->setOperation(CutterFilter::Keep);
}

void ConfigWidget::on_radioButtonRemove_toggled(bool checked) {
	if (!checked)
		return;

	filter()->setOperation(CutterFilter::Remove);
}

void ConfigWidget::languageChanged() {
	int comboBoxStartMarkerCurrentIndex = comboBoxStartMarkerPosition->currentIndex();
	int comboBoxEndMarkerCurrentIndex = comboBoxEndMarkerPosition->currentIndex();

	retranslateUi(this);

	comboBoxStartMarkerPosition->setCurrentIndex(comboBoxStartMarkerCurrentIndex);
	comboBoxEndMarkerPosition->setCurrentIndex(comboBoxEndMarkerCurrentIndex);
}
