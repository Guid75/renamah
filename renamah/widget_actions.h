#ifndef WIDGET_ACTIONS_H
#define WIDGET_ACTIONS_H

#include <QScrollArea>

#include "widget_modifiers.h"

class WidgetActions : public WidgetModifiers
{
	Q_OBJECT

public:
	WidgetActions(QWidget *parent = 0);

protected:
	void setConfigWidget(QWidget *widget);

private:
	QScrollArea *scrollAreaGeneral;
};

#endif
