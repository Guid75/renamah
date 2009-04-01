#include <QMessageBox>

#include "dialog_manual_rename.h"

DialogManualRename::DialogManualRename(QWidget *parent)
	: QDialog(parent),
	  _automaticRename(false)
{
	setupUi(this);
}

void DialogManualRename::init(const QString &originalFileName, const QString &newFileName)
{
	_originalFileName = originalFileName;
	lineEdit->setText(newFileName);
	lineEdit->selectAll();
}

void DialogManualRename::on_pushButtonAutomatic_clicked()
{
	_automaticRename = true;
	accept();
}

void DialogManualRename::on_pushButtonOriginal_clicked()
{
	if (QMessageBox::question(this, tr("Are you sure?"), tr("Do you really want to set the original filename?"), QMessageBox::Yes | QMessageBox::Cancel) !=
		QMessageBox::Yes)
		return;

	lineEdit->setText(_originalFileName);
}
