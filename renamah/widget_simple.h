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

private:
	int uiRetranslating;
	QMenu *menuSort;

	void refreshFileCount();
	void modifyCurrentFileName();

private slots:
	void on_pushButtonAddFiles_clicked();
	void on_pushButtonRemoveFiles_clicked();
	void on_pushButtonUpFiles_clicked();
	void on_pushButtonDownFiles_clicked();
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
};

#endif
