#ifndef LED_WIDGET_H
#define LED_WIDGET_H

#include <QWidget>

class LedWidget : public QWidget
{
	Q_OBJECT

public:
	LedWidget(QWidget *parent = 0) : QWidget(parent) {}

protected:
	void paintEvent(QPaintEvent *event);
};

#endif
