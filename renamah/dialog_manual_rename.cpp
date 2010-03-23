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

#include <QMessageBox>

#include "dialog_manual_rename.h"

DialogManualRename::DialogManualRename(QWidget *parent)
    : QDialog(parent),
    _automaticRename(false)
{
    setupUi(this);
}

void DialogManualRename::init(const QString &originalFileName, const QString &newFileName)
{
    _originalFileName = originalFileName;
    lineEdit->setText(newFileName);
    lineEdit->selectAll();
}

void DialogManualRename::on_pushButtonAutomatic_clicked()
{
    _automaticRename = true;
    accept();
}

void DialogManualRename::on_pushButtonOriginal_clicked()
{
    if (QMessageBox::question(this, tr("Are you sure?"), tr("Do you really want to set the original filename?"), QMessageBox::Yes | QMessageBox::Cancel) !=
        QMessageBox::Yes)
        return;

    lineEdit->setText(_originalFileName);
}
