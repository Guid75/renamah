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

#include <QDateTime>

#include "processor.h"
#include "form_last_operations.h"

FormLastOperations::FormLastOperations(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    connect(&Processor::instance(), SIGNAL(taskSuccess(const QString &, const QString &)),
            this, SLOT(taskSuccess(const QString &, const QString &)));
    connect(&Processor::instance(), SIGNAL(taskFailure(const QString &, const QString &, const QString &)),
            this, SLOT(taskFailure(const QString &, const QString &, const QString &)));
    connect(&Processor::instance(), SIGNAL(started()),
            this, SLOT(processorStarted()));
    connect(&Processor::instance(), SIGNAL(percentProgress(int)),
            this, SLOT(processorPercentProgress(int)));
}

void FormLastOperations::taskSuccess(const QString &original, const QString &renamed)
{
    plainTextEditResults->appendHtml(QString("<span style=\"color:#0000AA\"><b>%1</b></span>: %2 --> %3 : <span style=\"color:#00AA00\"><b>SUCCESS</b></span>").arg(Processor::instance().destinationOperationName()).arg(original).arg(renamed));
}

void FormLastOperations::taskFailure(const QString &original, const QString &renamed, const QString &errorMsg)
{
    plainTextEditResults->appendHtml(QString("<span style=\"color:#0000AA\"><b>%1</b></span>: %2 -> %3 : <span style=\"color:#AA0000\"><b>FAILURE</b></span> (%4)").arg(Processor::instance().destinationOperationName()).arg(original).arg(renamed).arg(errorMsg));
}

void FormLastOperations::processorStarted()
{
    plainTextEditResults->appendHtml(QString("<u><b>Renaming session started at %1</b></u>").arg(QDateTime::currentDateTime().toString()));
}

void FormLastOperations::processorPercentProgress(int percent)
{
    progressBar->setValue(percent);
}
