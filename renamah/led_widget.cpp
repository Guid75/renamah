#include <QPainter>

#include "led_widget.h"

void LedWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect r(0, 0, 16, 16);
	painter.drawPixmap(r, QPixmap(":/images/checked.png"));
}
