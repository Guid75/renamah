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

#ifndef WIDGET_MODIFIERS_H
#define WIDGET_MODIFIERS_H

#include <QMenu>
#include <QSignalMapper>

#include "modifier_manager.h"
#include "modifier_model.h"
#include "ui_widget_modifiers.h"

class WidgetModifiers : public QWidget, protected Ui::WidgetModifiers
{
	Q_OBJECT

public:
	WidgetModifiers(QWidget *parent = 0);

	virtual void init(ModifierManager *modifierManager, ModifierModel &modifierModel);
	/*! Called after each profile loaded */
	virtual void newProfile();

public slots:
	void addModifier(const QString &factoryName);

protected:
	bool eventFilter(QObject *obj, QEvent *ev);
	void changeEvent(QEvent *event);

	core::Modifier *currentModifier() const;
	virtual void setConfigWidget(QWidget *widget) = 0;
	virtual void currentModifierChanged(core::Modifier *modifier) {};

private:
	core::ModifierConfigWidget *_configWidget;
	QMenu menuAddModifier;
	QSignalMapper signalMapperAddModifier;

	ModifierManager *_modifierManager;
	ModifierModel *_modifierModel;

	QRect modifierStateRect(const QModelIndex &index) const;
	QRect modifierOnlyRect(const QModelIndex &index) const;

	void retranslate();

private slots:
	void on_pushButtonRemove_clicked();
	void on_pushButtonUp_clicked();
	void on_pushButtonDown_clicked();
	void aboutToShowAddModifierMenu();
	void currentModifierChanged(const QModelIndex &current, const QModelIndex &previous);
	void widgetModifierChanged();
	void modifiersInserted(const QModelIndex &parent, int start, int end);
};

#endif
