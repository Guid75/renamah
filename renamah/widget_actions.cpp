#include "widget_actions.h"

WidgetActions::WidgetActions(QWidget *parent)
	: WidgetModifiers(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(widgetConfig);
	mainLayout->setMargin(0);

	// Constructs actions specific widgets
	scrollAreaGeneral = new QScrollArea;
	scrollAreaGeneral->setFrameShape(QFrame::NoFrame);
	scrollAreaGeneral->setWidgetResizable(true);
	mainLayout->addWidget(scrollAreaGeneral);
}

void WidgetActions::setConfigWidget(QWidget *widget)
{
	scrollAreaGeneral->setWidget(widget);
}
