#ifndef FORM_TWINNING_H
#define FORM_TWINNING_H

#include <QDirModel>
#include <QString>
#include <QRegExp>

#include "simple_dir_model.h"

#include "ui_form_twinning.h"

class FormTwinning : public QWidget, private Ui::FormTwinning
{
     Q_OBJECT

public:
     FormTwinning(QWidget *parent = 0);

protected:
     bool eventFilter(QObject *watched, QEvent *event);

private:
     bool _chainedDir;
     QString _leftPath;
     QString _rightPath;
     SimpleDirModel *_leftModel;
     SimpleDirModel *_rightModel;
     QMap<int, QList<int> > _twinning;

     void init();
     void refreshChainModeButton();
     void validateLeftDir(bool subcall = false);
     void validateRightDir(bool subcall = false);
     void validateLeftExtension();
     void validateRightExtension();
     void redoTwinning();
     QStringList atomize(const QString &text) const;
     int challenge(const QStringList &atoms1, const QStringList &atoms2) const;
     bool isEpisodeNumberString(const QString &text, int &season, int &episode) const;
     QFileInfo leftFileInfo(int row) const;
     QFileInfo rightFileInfo(int row) const;
     bool isFree(int leftRow, int score) const;

private slots:
     void on_pushButtonChainMode_clicked();
     void on_toolButtonLeftDir_clicked();
     void on_toolButtonRightDir_clicked();
     void on_comboBoxLeftExtension_currentIndexChanged(const QString &text);
     void on_comboBoxRightExtension_currentIndexChanged(const QString &text);
     void leftTreeVerticalScrollBarValueChanged(int value);
     void rightTreeVerticalScrollBarValueChanged(int value);
     void leftModelReset();
     void leftRowsInserted(const QModelIndex &parent, int start, int end);
     void leftRowsRemoved(const QModelIndex &parent, int start, int end);
     void rightModelReset();
     void rightRowsInserted(const QModelIndex &parent, int start, int end);
     void rightRowsRemoved(const QModelIndex &parent, int start, int end);
     void currentLeftRowChanged(const QModelIndex &current, const QModelIndex &previous);
     void currentRightRowChanged(const QModelIndex &current, const QModelIndex &previous);
     void on_pushButtonProcess_clicked();
};

#endif
