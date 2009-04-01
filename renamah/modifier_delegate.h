#ifndef MODIFIER_DELEGATE_H
#define MODIFIER_DELEGATE_H

#include <QStyledItemDelegate>
#include <QTreeView>

class ModifierDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	ModifierDelegate(QObject *parent = 0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
	QRect getStateRect() const;
};

#endif
