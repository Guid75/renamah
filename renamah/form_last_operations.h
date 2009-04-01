#ifndef FORM_LAST_OPERATIONS_H
#define FORM_LAST_OPERATIONS_H

#include "ui_form_last_operations.h"

class FormLastOperations : public QWidget, private Ui::FormLastOperations
{
     Q_OBJECT

public:
     FormLastOperations(QWidget *parent = 0);

private slots:
	void taskSuccess(const QString &original, const QString &renamed);
	void taskFailure(const QString &original, const QString &renamed, const QString &errorMsg);
	void processorStarted();
	void processorPercentProgress(int percent);
};

#endif
