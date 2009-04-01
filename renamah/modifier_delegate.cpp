#include <QPainter>

#include "modifier_model.h"
#include "led_widget.h"
#include "modifier_delegate.h"

ModifierDelegate::ModifierDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
}

void ModifierDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::paint(painter, option, index);

	const ModifierModel *model = qobject_cast<const ModifierModel*>(index.model());
	Q_ASSERT_X(model, "ModifierDelegate()", "index.model() is not a ModifierModel!");
	core::Modifier *modifier = model->modifier(index);
	switch (index.column())
    {
	case ModifierModel::colMode:
	{
		painter->save();

		QRect centerRect = option.rect;
		centerRect.setWidth(qMin(centerRect.width(), 32));
		centerRect.setHeight(qMin(centerRect.height(), 16));
		int dx = 0;
		if (centerRect.width() == 32 && option.rect.width() > 32)
			dx = option.rect.width() / 2 - 16;
		int dy = 0;
		if (centerRect.height() == 32 && option.rect.height() > 32)
			dy = option.rect.height() / 2 - 16;
		centerRect.translate(dx, dy);
		QRect leftRect = centerRect;
		leftRect.setWidth(16);
		QRect rightRect = centerRect;
		rightRect.setWidth(16);
		rightRect.translate(16, 0);
		if (model->modifierState(modifier))
		{
			if (!model->exclusiveModifier() ||
				model->exclusiveModifier() == modifier)
				painter->drawPixmap(leftRect, QPixmap(":/images/filter-on.png"));
			else
				painter->drawPixmap(leftRect, QPixmap(":/images/filter-on-single.png"));
		} else
			painter->drawPixmap(leftRect, QPixmap(":/images/filter-off.png"));
		if (model->exclusiveModifier() == modifier)
			painter->drawPixmap(rightRect, QPixmap(":/images/filter-single-on.png"));
		else
			painter->drawPixmap(rightRect, QPixmap(":/images/filter-single-off.png"));

		painter->restore();
		return;
	}
	default:;
	}
}
