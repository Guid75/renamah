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

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QThread>
#include <QPair>

class Processor : public QThread
{
    Q_OBJECT

public:
    enum DestinationOperation {
        Rename,
        Copy,
        Move,
        SymLink
    };

    static Processor &instance();

    void clearTasks();
    void addTask(const QString &oldFileName, const QString &newFileName);
    bool hasTasks() const { return tasks.count(); }

    DestinationOperation destinationOperation() const { return _destinationOperation; }
    void setDestinationOperation(DestinationOperation operation);
    QString destinationOperationName() const;
    const QString &destinationDir() const { return _destinationDir; }
    void setDestinationDir(const QString &dir);

    void go();

signals:
    void taskSuccess(const QString &original, const QString &renamed);
    void taskFailure(const QString &original, const QString &renamed, const QString &errorMsg);
    void percentProgress(int percent);

protected:
    void run();

private:
    static Processor *_instance;
    QList<QPair<QString,QString> > tasks;
    //	QList<QPair<QString,QString> > failed;
    //	QList<QPair<QString,QString> > succeed;
    int _lastPercent;
    DestinationOperation _destinationOperation;
    QString _destinationDir;

    Processor(QObject *parent = 0);
};

#endif
