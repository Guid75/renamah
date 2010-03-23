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

#ifndef DIALOG_MANUAL_RENAME_H
#define DIALOG_MANUAL_RENAME_H

#include "ui_dialog_manual_rename.h"

class DialogManualRename : public QDialog, private Ui::DialogManualRename
{
    Q_OBJECT

public:
    DialogManualRename(QWidget *parent = 0);

    void init(const QString &originalFileName, const QString &newFileName);

    bool automaticRename() const { return _automaticRename; }
    QString fileName() const { return lineEdit->text(); }

private:
    QString _originalFileName;
    bool _automaticRename;

private slots:
    void on_pushButtonAutomatic_clicked();
    void on_pushButtonOriginal_clicked();
};

#endif
