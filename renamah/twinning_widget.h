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
