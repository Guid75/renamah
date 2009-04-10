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
	void filterDropDone();
	void modifiersInserted(const QModelIndex &parent, int start, int end);
};

#endif
