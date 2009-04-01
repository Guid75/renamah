#ifndef TWINNING_WIDGET_H
#define TWINNING_WIDGET_H

#include <QWidget>
#include <QTreeView>

class TwinningWidget : public QWidget
{
     Q_OBJECT

public:
     TwinningWidget(QWidget *parent = 0)
          : QWidget(parent),
            _leftTree(0),
            _rightTree(0) {}

     void setTrees(QTreeView *leftTree, QTreeView *rightTree);

     void setTwinning(const QMap<int, QList<int> > &twinning);

protected:
     void paintEvent(QPaintEvent *event);

private:
     static const int _priorityColors[];

     QTreeView *_leftTree;
     QTreeView *_rightTree;
     QMap<int, QList<int> > _twinning;

     void drawLinks(QPainter &painter);
};

#endif
