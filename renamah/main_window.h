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

#include <QMenu>
#include <QSignalMapper>
#include <QTranslator>
#include <QActionGroup>

#include "ui_main_window.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

protected:
    void changeEvent(QEvent *event);

private:
    QMenu menuLanguages;
    QActionGroup *actionGroupLanguages;
    QSignalMapper signalMapperLanguages;
    QList<QTranslator*> translators;

    void refreshLanguageActions();

    void installLanguage(const QString &language);

private slots:
    void processorStarted();
    void languageRequested(const QString &language);
    void on_actionLoadProfile_triggered();
    void on_actionSaveProfile_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
};
