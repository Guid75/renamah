#ifndef DIALOG_MANUAL_RENAME_H
#define DIALOG_MANUAL_RENAME_H

#include "ui_dialog_manual_rename.h"

class DialogManualRename : public QDialog, private Ui::DialogManualRename
{
	Q_OBJECT

public:
	DialogManualRename(QWidget *parent = 0);

	void init(const QString &originalFileName, const QString &newFileName);

	bool automaticRename() const { return _automaticRename; }
	QString fileName() const { return lineEdit->text(); }

private:
	QString _originalFileName;
	bool _automaticRename;

private slots:
	void on_pushButtonAutomatic_clicked();
	void on_pushButtonOriginal_clicked();
};

#endif
