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
