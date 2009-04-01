#include <QPainter>
#include <QDirModel>

#include "twinning_widget.h"

const int TwinningWidget::_priorityColors[] = {
     Qt::red,
     Qt::blue,
     Qt::green
};

void TwinningWidget::paintEvent(QPaintEvent *event)
{
     QPainter painter(this);

     painter.setRenderHint(QPainter::Antialiasing, true);

     QPen pen(Qt::red);
     pen.setWidth(2);
     painter.setPen(pen);

     drawLinks(painter);

//     QWidget::paintEvent(event);
}

void TwinningWidget::setTrees(QTreeView *leftTree, QTreeView *rightTree)
{
     _leftTree = leftTree;
     _rightTree = rightTree;

     update();
}

void TwinningWidget::drawLinks(QPainter &painter)
{
     if (!_leftTree || !_rightTree)
          return;

     QDirModel *leftModel = qobject_cast<QDirModel*>(_leftTree->model());
     QDirModel *rightModel = qobject_cast<QDirModel*>(_rightTree->model());

     foreach (int row, _twinning.keys())
     {
          QModelIndex leftIndex = leftModel->index(row, 0, _leftTree->rootIndex());
          QFileInfo leftFileInfo = leftModel->fileInfo(leftIndex);
          QRect leftVisualRect = _leftTree->visualRect(leftIndex);
          QPoint leftPoint(0, leftVisualRect.y() + leftVisualRect.height() / 2 + _leftTree->viewport()->y());

          QPen pen = painter.pen();
          int count = _twinning[row].count();
          int offset = 0;

          foreach (int rightRow, _twinning[row])
          {
               QModelIndex rightIndex = rightModel->index(rightRow, 0, _rightTree->rootIndex());
               QFileInfo rightFileInfo = rightModel->fileInfo(rightIndex);
               QRect rightVisualRect = _rightTree->visualRect(rightIndex);
               QPoint rightPoint(width(), rightVisualRect.y() + rightVisualRect.height() / 2 + _rightTree->viewport()->y());

               if (leftFileInfo.completeBaseName() == rightFileInfo.completeBaseName())
                    pen.setColor(Qt::green);
               else
                    pen.setColor(Qt::red);
               painter.setPen(pen);
               painter.drawLine(leftPoint, rightPoint);
               offset++;
          }
     }
}

void TwinningWidget::setTwinning(const QMap<int, QList<int> > &twinning)
{
     _twinning = twinning;
     update();
}
