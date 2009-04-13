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

ConfigWidget::ConfigWidget() :
     core::ModifierConfigWidget() {
	setupUi(this);

	_radioButton2Operation.insert(radioButtonLowerCase, CaseFilter::LowerCase);
	_radioButton2Operation.insert(radioButtonUpperCase, CaseFilter::UpperCase);
	_radioButton2Operation.insert(radioButtonFirstLetter, CaseFilter::UpFirstLetter);
	_radioButton2Operation.insert(radioButtonFirstWordsLetter, CaseFilter::UpWordsFirstLetter);

	connect(radioButtonLowerCase, SIGNAL(toggled(bool)), this, SLOT(operationRadioButtonToggled(bool)));
	connect(radioButtonUpperCase, SIGNAL(toggled(bool)), this, SLOT(operationRadioButtonToggled(bool)));
	connect(radioButtonFirstLetter, SIGNAL(toggled(bool)), this, SLOT(operationRadioButtonToggled(bool)));
	connect(radioButtonFirstWordsLetter, SIGNAL(toggled(bool)), this, SLOT(operationRadioButtonToggled(bool)));
}

void ConfigWidget::refreshControls() {
	CaseFilter *caseFilter = static_cast<CaseFilter*>(modifier());

	// Refresh controls
	QRadioButton *radioButton = _radioButton2Operation.key(caseFilter->operation());
	radioButton->setChecked(true);

	checkBoxDontLowerOtherChars->setVisible(
		caseFilter->operation() == CaseFilter::UpFirstLetter ||
		caseFilter->operation() == CaseFilter::UpWordsFirstLetter);
	checkBoxDontLowerOtherChars->setChecked(!caseFilter->lowerOtherChars());
}

void ConfigWidget::on_checkBoxDontLowerOtherChars_toggled(bool checked) {
	CaseFilter *caseFilter = static_cast<CaseFilter*>(modifier());
	caseFilter->setLowerOtherChars(!checked);
}

void ConfigWidget::operationRadioButtonToggled(bool checked) {
	if (!checked)
		return;

	CaseFilter *caseFilter = static_cast<CaseFilter*>(modifier());
	caseFilter->setOperation(_radioButton2Operation[qobject_cast<QRadioButton*>(sender())]);

//	configControls();
}

void ConfigWidget::languageChanged() {
	retranslateUi(this);
}
