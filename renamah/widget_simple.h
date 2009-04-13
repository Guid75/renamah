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

#ifndef WIDGET_SIMPLE_H
#define WIDGET_SIMPLE_H

#include <QMenu>

#include <interfaces/filter.h>
#include <interfaces/action.h>
#include <interfaces/modifier_config_widget.h>

#include "ui_widget_simple.h"

class WidgetSimple : public QWidget, private Ui::WidgetSimple
{
	Q_OBJECT

public:
	WidgetSimple(QWidget *parent = 0);

	void initAfterPluginLoaded();
	/*! Called after each profile loaded */
	void newProfile();

protected:
	bool eventFilter(QObject *watched, QEvent *event);
	void changeEvent(QEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);

private:
	int uiRetranslating;
	QMenu *menuSort;

	void refreshFileCount();
	void modifyCurrentFileName();

private slots:
	void on_pushButtonAddFiles_clicked() { actionAddFiles->trigger(); }
	void on_pushButtonRemoveFiles_clicked() { actionRemoveSelectedFiles->trigger(); }
	void on_pushButtonUpFiles_clicked() { actionUpSelectedFiles->trigger(); }
	void on_pushButtonDownFiles_clicked() { actionDownSelectedFiles->trigger(); }
	void on_pushButtonProcess_clicked();
	void on_comboBoxOperation_currentIndexChanged(int index);
	void on_toolButtonDestination_clicked();
	void filesInserted(const QModelIndex &, int, int) { refreshFileCount(); }
	void filesRemoved(const QModelIndex &, int, int) { refreshFileCount(); }
	void filesModelReset() { refreshFileCount(); }
	void filesDropDone();
	void generalExtensionPolicyChanged();
	void on_actionSortByName_triggered();
	void on_actionSortByModificationDate_triggered();
	void on_actionRemoveSelectedFiles_triggered();
	void on_actionAddFiles_triggered();
	void on_actionUpSelectedFiles_triggered();
	void on_actionDownSelectedFiles_triggered();
	void treeViewFilesSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
};

#endif
