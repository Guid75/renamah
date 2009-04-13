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

#include <QDir>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMouseEvent>
#include <QScrollBar>

#include "form_twinning.h"

FormTwinning::FormTwinning(QWidget *parent)
     : QWidget(parent),
       _chainedDir(true)
{
     setupUi(this);

     init();
}

bool FormTwinning::eventFilter(QObject *watched, QEvent *event)
{
     switch (event->type())
     {
     case QEvent::KeyPress:
     {
          QKeyEvent *keyEvent = dynamic_cast<QKeyEvent*>(event);
          if (keyEvent->key() == Qt::Key_Return)
          {
               if (watched == lineEditLeftDir)
                    validateLeftDir();
               else if (watched == lineEditRightDir)
                    validateRightDir();
               else if (watched == comboBoxLeftExtension)
                    validateLeftExtension();
               else if (watched == comboBoxRightExtension)
                    validateRightExtension();
          }
     }
     break;
     case QEvent::MouseButtonDblClick:
     {
          QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
          if (watched == treeViewLeft->viewport())
          {
               QModelIndex index = treeViewLeft->indexAt(mouseEvent->pos());
               if (index.isValid() && _leftModel->fileInfo(index).isDir())
               {
                    lineEditLeftDir->setText(_leftModel->filePath(index));
                    validateLeftDir();
               }
          } else if (watched == treeViewRight->viewport())
          {
               QModelIndex index = treeViewRight->indexAt(mouseEvent->pos());
               if (index.isValid() && _rightModel->fileInfo(index).isDir())
               {
                    lineEditRightDir->setText(_rightModel->filePath(index));
                    validateRightDir();
               }
          }
     }
     break;
     default:;
     }

     return QWidget::eventFilter(watched, event);
}

void FormTwinning::init()
{
     lineEditLeftDir->installEventFilter(this);
     lineEditRightDir->installEventFilter(this);
     comboBoxLeftExtension->installEventFilter(this);
     comboBoxRightExtension->installEventFilter(this);
     treeViewLeft->viewport()->installEventFilter(this);
     treeViewRight->viewport()->installEventFilter(this);
     connect(treeViewLeft->verticalScrollBar(), SIGNAL(valueChanged(int)),
             this, SLOT(leftTreeVerticalScrollBarValueChanged(int)));
     connect(treeViewRight->verticalScrollBar(), SIGNAL(valueChanged(int)),
             this, SLOT(rightTreeVerticalScrollBarValueChanged(int)));

     treeViewLeft->setModel(_leftModel = new SimpleDirModel);
     _leftModel->setFilter(QDir::Files | QDir::AllDirs);
     _leftModel->setSorting(QDir::Name | QDir::IgnoreCase | QDir::DirsFirst);
     connect(_leftModel, SIGNAL(modelReset()), this, SLOT(leftModelReset()));
     connect(_leftModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
             this, SLOT(leftRowsInserted(const QModelIndex &, int, int)));
     connect(_leftModel, SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
             this, SLOT(leftRowsRemoved(const QModelIndex &, int, int)));
     connect(treeViewLeft->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)),
             this, SLOT(currentLeftRowChanged(const QModelIndex&, const QModelIndex&)));

     treeViewRight->setModel(_rightModel = new SimpleDirModel);
     _rightModel->setFilter(QDir::Files | QDir::AllDirs);
     _rightModel->setSorting(QDir::Name | QDir::IgnoreCase | QDir::DirsFirst);
    connect(_rightModel, SIGNAL(modelReset()), this, SLOT(rightModelReset()));
     connect(_rightModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
             this, SLOT(rightRowsInserted(const QModelIndex &, int, int)));
     connect(_rightModel, SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
             this, SLOT(rightRowsRemoved(const QModelIndex &, int, int)));
     connect(treeViewRight->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)),
             this, SLOT(currentRightRowChanged(const QModelIndex&, const QModelIndex&)));

     refreshChainModeButton();

     comboBoxLeftExtension->lineEdit()->setText("*.avi,*.mkv");
     validateLeftExtension();

     comboBoxRightExtension->lineEdit()->setText("*.srt,*.sub");
     validateRightExtension();

     lineEditLeftDir->setText(QDir::home().absolutePath());
     validateLeftDir();

     widgetTwinning->setTrees(treeViewLeft, treeViewRight);
}

void FormTwinning::refreshChainModeButton()
{
     if (_chainedDir)
          pushButtonChainMode->setIcon(QIcon(":/images/chained.png"));
     else
          pushButtonChainMode->setIcon(QIcon(":/images/unchained.png"));
}

void FormTwinning::on_pushButtonChainMode_clicked()
{
     // Toggle
     _chainedDir = !_chainedDir;
     refreshChainModeButton();
}

void FormTwinning::validateLeftDir(bool subcall)
{
     if (_leftPath == lineEditLeftDir->text())
          return;

     _leftPath = lineEditLeftDir->text();
     if (_chainedDir && _rightPath != _leftPath)
     {
          lineEditRightDir->setText(_leftPath);
          validateRightDir(true);
     }

     treeViewLeft->setRootIndex(_leftModel->index(_leftPath));
     treeViewLeft->resizeColumnToContents(0);

     if (!subcall)
          redoTwinning();

     widgetTwinning->update();
}

void FormTwinning::validateRightDir(bool subcall)
{
     if (_rightPath == lineEditRightDir->text())
          return;

     _rightPath = lineEditRightDir->text();
     if (_chainedDir && _leftPath != _rightPath)
     {
          lineEditLeftDir->setText(_rightPath);
          validateLeftDir(true);
     }

     treeViewRight->setRootIndex(_rightModel->index(_rightPath));
     treeViewRight->resizeColumnToContents(0);

     if (!subcall)
          redoTwinning();

     widgetTwinning->update();
}

void FormTwinning::validateLeftExtension()
{
     QStringList nameFilters = comboBoxLeftExtension->currentText().split(",");
     _leftModel->setNameFilters(nameFilters);
     treeViewLeft->resizeColumnToContents(0);
     widgetTwinning->update();
}

void FormTwinning::validateRightExtension()
{
     QStringList nameFilters = comboBoxRightExtension->currentText().split(",");
     _rightModel->setNameFilters(nameFilters);
     treeViewRight->resizeColumnToContents(0);
     widgetTwinning->update();
}

void FormTwinning::on_toolButtonLeftDir_clicked()
{
     QString dirPath = QFileDialog::getExistingDirectory(this, tr("Choose a directory for left files"),
                                                         _leftPath);
     if (dirPath == "")
          return;

     lineEditLeftDir->setText(dirPath);
     validateLeftDir();
}

void FormTwinning::on_toolButtonRightDir_clicked()
{
     QString dirPath = QFileDialog::getExistingDirectory(this, tr("Choose a directory for right files"),
                                                         _rightPath);
     if (dirPath == "")
          return;

     lineEditRightDir->setText(dirPath);
     validateRightDir();
}

void FormTwinning::on_comboBoxLeftExtension_currentIndexChanged(const QString &text)
{
     validateLeftExtension();
}

void FormTwinning::on_comboBoxRightExtension_currentIndexChanged(const QString &text)
{
     validateRightExtension();
}

void FormTwinning::leftTreeVerticalScrollBarValueChanged(int)
{
     widgetTwinning->update();
}

void FormTwinning::rightTreeVerticalScrollBarValueChanged(int)
{
     widgetTwinning->update();
}

void FormTwinning::leftModelReset()
{
}

void FormTwinning::leftRowsInserted(const QModelIndex &parent, int start, int end)
{
}

void FormTwinning::leftRowsRemoved(const QModelIndex &parent, int start, int end)
{
}

void FormTwinning::rightModelReset()
{
}

void FormTwinning::rightRowsInserted(const QModelIndex &parent, int start, int end)
{
}

void FormTwinning::rightRowsRemoved(const QModelIndex &parent, int start, int end)
{
}

QFileInfo FormTwinning::leftFileInfo(int row) const
{
     return _leftModel->fileInfo(_leftModel->index(row, 0, treeViewLeft->rootIndex()));
}

QFileInfo FormTwinning::rightFileInfo(int row) const
{
     return _rightModel->fileInfo(_rightModel->index(row, 0, treeViewRight->rootIndex()));
}

bool pairSortLessThan(const QPair<int,int> pair1, const QPair<int,int> pair2)
{
     return pair1.second < pair2.second;
}

void FormTwinning::redoTwinning()
{
     _twinning.clear();

     // Build left atoms
     QMap<int, QStringList> leftAtomsMapping;
     for (int row = 0; row < _leftModel->rowCount(treeViewLeft->rootIndex()); ++row)
     {
          QFileInfo fileInfo = leftFileInfo(row);
          if (fileInfo.isFile())
               leftAtomsMapping.insert(row, atomize(fileInfo.completeBaseName()));
     }

     // Association of every right row with an ordered list of pairs representing a left row and a score
     QMap<int, QList<QPair<int, int> > > mapping;
     for (int rightRow = 0; rightRow < _rightModel->rowCount(treeViewRight->rootIndex()); ++rightRow)
     {
          QList<QPair<int, int> > scores;
          QStringList rightAtoms = atomize(rightFileInfo(rightRow).completeBaseName());

          for (int leftRow = 0; leftRow < _leftModel->rowCount(treeViewLeft->rootIndex()); ++leftRow)
               scores << QPair<int, int>(leftRow, challenge(leftAtomsMapping[leftRow], rightAtoms));

          // Sort it by score
          qSort(scores.begin(), scores.end(), pairSortLessThan);

          mapping.insert(rightRow, scores);
     }

     for (int rightRow = 0; rightRow < _rightModel->rowCount(treeViewRight->rootIndex()); ++rightRow)
     {
          const QList<QPair<int, int> > &scores = mapping[rightRow];
          for (int i = scores.count() - 1; i >= 0; --i)
          {
               int leftRow = scores[i].first;
               int score = scores[i].second;
               if (isFree(leftRow, score))
               {
                    _twinning.insert(leftRow, QList<int>() << rightRow);

                    // Remove this left row from mapping
                    for (int rightRow = 0; rightRow < _rightModel->rowCount(treeViewRight->rootIndex()); ++rightRow)
                    {
                         QList<QPair<int, int> > &scores = mapping[rightRow];
                         for (int i = 0; i < scores.count(); ++i)
                              if (scores[i].first == leftRow)
                              {
                                   scores.removeAt(i);
                                   break;
                              }
                    }

                    break;
               }
          }
     }

     widgetTwinning->setTwinning(_twinning);
 }

bool FormTwinning::isFree(int leftRow, int score) const
{
     return true;
}

void FormTwinning::currentLeftRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
     QMap<int, QList<int> >::const_iterator it = _twinning.find(current.row());
     if (it == _twinning.end())
          return;

     treeViewRight->selectionModel()->setCurrentIndex(_rightModel->index((*it)[0], 0, treeViewRight->rootIndex()),
                                                      QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
}

void FormTwinning::currentRightRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
}

QStringList FormTwinning::atomize(const QString &text) const
{
     QStringList atoms;

     QRegExp regExp("[\\da-zA-z]+");
     int count = 0;
     int pos = 0;
     while ((pos = regExp.indexIn(text, pos)) != -1) {
          ++count;
          atoms << text.mid(pos, regExp.matchedLength());
          pos += regExp.matchedLength();
     }

     return atoms;
}

int FormTwinning::challenge(const QStringList &atoms1, const QStringList &atoms2) const
{
     int score = 0;
     QStringList tmpAtoms2 = atoms2;
     QList<QPair<int,int> > remainEpNumbers;

     // Simple string correspondances
     foreach (const QString &atom, atoms1)
     {
          int index = tmpAtoms2.indexOf(QRegExp(atom, Qt::CaseInsensitive, QRegExp::FixedString));
          if (index >= 0)
          {
               score++;
               tmpAtoms2.removeAt(index);
          } else
          {
               int season = -1;
               int episode = -1;
               if (isEpisodeNumberString(atom, season, episode))
                    remainEpNumbers << QPair<int,int>(season, episode);
          }
     }

     foreach (const QString &atom, tmpAtoms2)
     {
          int season = -1;
          int episode = -1;
          if (isEpisodeNumberString(atom, season, episode))
          {
               int index = remainEpNumbers.indexOf(QPair<int,int>(season, episode));
               if (index >= 0)
               {
                    score += 10;
                    remainEpNumbers.removeAt(index);
               }
          }
     }

     return score;
}

bool FormTwinning::isEpisodeNumberString(const QString &text, int &season, int &episode) const
{
     QRegExp epNumRegExp1("S(\\d+)E(\\d+)", Qt::CaseInsensitive);
     QRegExp epNumRegExp2("(\\d+)x(\\d+)", Qt::CaseInsensitive);
     QRegExp epNumRegExp3("(\\d)(\\d{2})", Qt::CaseInsensitive);

     if (epNumRegExp1.exactMatch(text))
     {
          season = epNumRegExp1.cap(1).toInt();
          episode = epNumRegExp1.cap(2).toInt();
     } else if (epNumRegExp2.exactMatch(text))
     {
          season = epNumRegExp2.cap(1).toInt();
          episode = epNumRegExp2.cap(2).toInt();
     } else if (epNumRegExp3.exactMatch(text))
     {
          season = epNumRegExp3.cap(1).toInt();
          episode = epNumRegExp3.cap(2).toInt();
     } else
          return false;
     return true;
}

void FormTwinning::on_pushButtonProcess_clicked()
{
     foreach (int leftRow, _twinning.keys())
     {
          int rightRow = _twinning[leftRow][0];

          QFileInfo leftFileInfo = _leftModel->fileInfo(_leftModel->index(leftRow, 0, treeViewLeft->rootIndex()));
          QFileInfo rightFileInfo = _rightModel->fileInfo(_rightModel->index(rightRow, 0, treeViewRight->rootIndex()));

          if (leftFileInfo.completeBaseName() != rightFileInfo.completeBaseName())
          {
               QString oldName = rightFileInfo.absoluteFilePath();
               QString newName = QDir(rightFileInfo.absolutePath()).filePath(leftFileInfo.completeBaseName() + '.' +
                                                                             rightFileInfo.suffix());
               QFile::rename(oldName, newName);
          }
     }
     _rightModel->refresh();
     redoTwinning();
}
