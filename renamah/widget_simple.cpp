#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QKeyEvent>
#include <QMouseEvent>

#include <interfaces/filter_factory.h>

#include "file_model.h"
#include "filter_model.h"
#include "filter_manager.h"
#include "processor.h"
#include "finalizer_model.h"
#include "action_manager.h"
#include "dialog_manual_rename.h"
#include "widget_simple.h"

WidgetSimple::WidgetSimple(QWidget *parent)
	: uiRetranslating(false), QWidget(parent) {
	setupUi(this);

	menuSort = new QMenu(this);
	pushButtonSort->setMenu(menuSort);
	menuSort->addAction(actionSortByName);
	menuSort->addAction(actionSortByModificationDate);

	// Filters
	widgetFilters->init(&FilterManager::instance(), FilterModel::instance());
	connect(&FilterModel::instance(), SIGNAL(modifiersChanged()),
			&FileModel::instance(), SLOT(invalidate()));
	refreshFileCount();

	// Finalizers
	widgetFinalizers->init(&ActionManager::instance(), FinalizerModel::instance());
	connect(&FinalizerModel::instance(), SIGNAL(modifiersChanged()),
			&FileModel::instance(), SLOT(invalidate()));

	// Files
	treeViewFiles->setModel(&FileModel::instance());
	treeViewFiles->header()->resizeSection(0, width() / 2);
	connect(&FileModel::instance(), SIGNAL(rowsInserted(const QModelIndex &, int, int)),
			this, SLOT(filesInserted(const QModelIndex &, int, int)));
	connect(&FileModel::instance(), SIGNAL(rowsRemoved(const QModelIndex &, int, int)),
			this, SLOT(filesRemoved(const QModelIndex &, int, int)));
	connect(&FileModel::instance(), SIGNAL(modelReset()),
			this, SLOT(filesModelReset()));
	connect(&FileModel::instance(), SIGNAL(dropDone()),
			this, SLOT(filesDropDone()));
	connect(treeViewFiles->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
			this, SLOT(treeViewFilesSelectionChanged(const QItemSelection &, const QItemSelection &)));

	treeViewFiles->installEventFilter(this);
	treeViewFiles->viewport()->installEventFilter(this);

	labelAddFiles->installEventFilter(this);

	on_comboBoxOperation_currentIndexChanged(0);

	tabWidgetOperations->setCurrentWidget(tabFilters);

	widgetExtensionPolicy->setExtensionPolicy(FilterModel::instance().extensionPolicy());
	connect(widgetExtensionPolicy, SIGNAL(extensionPolicyChanged()),
			this, SLOT(generalExtensionPolicyChanged()));

	QList<int> sizes;
	sizes << 0 << 260;
	splitter->setSizes(sizes);
}

void WidgetSimple::initAfterPluginLoaded() {
    widgetFilters->addModifier("date");
    widgetFilters->addModifier("cutter");
    widgetFilters->addModifier("numbering");
//    widgetFinalizers->addModifier("command");

	// TEMP : Fill with some files
	foreach (const QFileInfo &fileInfo, QDir::home().entryInfoList(QDir::Files))
		FileModel::instance().addFile(fileInfo.absoluteFilePath());

	if (FileModel::instance().rowCount())
		stackedWidgetFiles->setCurrentWidget(pageFiles);
}

void WidgetSimple::on_pushButtonProcess_clicked() {
	// Fill processor with tasks
	Processor::instance().clearTasks();
	for (int row = 0; row < FileModel::instance().rowCount(); ++row)
	{
		QString original = FileModel::instance().originalFileName(FileModel::instance().index(row, 0));
		QString renamed = FilterModel::instance().apply(original, row);
		if (renamed != original)
			Processor::instance().addTask(original, FilterModel::instance().apply(original, row));
	}

	if (!Processor::instance().hasTasks() ||
		QMessageBox::question(this, tr("Are you sure?"), tr("Do you really want to start the rename process?"),
							  QMessageBox::Yes | QMessageBox::Cancel) != QMessageBox::Yes)
		return;

	Processor::instance().go();
}

void WidgetSimple::on_comboBoxOperation_currentIndexChanged(int index) {
	if (uiRetranslating)
		return;

	switch (index)
	{
	case 0:
		lineEditDestination->setEnabled(false);
		toolButtonDestination->setEnabled(false);
		Processor::instance().setDestinationOperation(Processor::Rename);
		break;
	default:
		lineEditDestination->setEnabled(true);
		toolButtonDestination->setEnabled(true);
		switch (index)
		{
		case 1:
			Processor::instance().setDestinationOperation(Processor::Copy);
			break;
		case 2:
			Processor::instance().setDestinationOperation(Processor::Move);
			break;
		case 3:
			Processor::instance().setDestinationOperation(Processor::SymLink);
			break;
		default:;
		}
		if (lineEditDestination->text() == "")
			on_toolButtonDestination_clicked();
	}
}

void WidgetSimple::on_toolButtonDestination_clicked() {
	QString dirName = "";
	if (QDir(lineEditDestination->text()).exists())
		dirName = lineEditDestination->text();

	dirName = QFileDialog::getExistingDirectory(this, tr("Choose a destination directory"), dirName);
	if (dirName == "")
		return;

	lineEditDestination->setText(dirName);

	Processor::instance().setDestinationDir(dirName);
}

void WidgetSimple::refreshFileCount() {
	labelFileCount->setText(tr("%n files", "", FileModel::instance().rowCount()));
}

void WidgetSimple::generalExtensionPolicyChanged() {
	FilterModel::instance().setExtensionPolicy(widgetExtensionPolicy->extensionPolicy());
}

bool WidgetSimple::eventFilter(QObject *watched, QEvent *event) {
	if (watched == treeViewFiles && event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Delete)
			on_pushButtonRemoveFiles_clicked();
	} else if (watched == treeViewFiles->viewport() && event->type() == QEvent::MouseButtonDblClick) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button() == Qt::LeftButton)
			modifyCurrentFileName();
	} else if (watched == labelAddFiles && event->type() == QEvent::MouseButtonPress) {
		actionAddFiles->trigger();
	}
	return QWidget::eventFilter(watched, event);
}

void WidgetSimple::modifyCurrentFileName() {
	QModelIndex index = treeViewFiles->currentIndex();
	if (!index.isValid())
		return;

	QDir dir = QFileInfo(FileModel::instance().originalFileName(index)).absoluteDir();

	DialogManualRename dialog(this);
	dialog.init(QFileInfo(FileModel::instance().originalFileName(index)).fileName(),
				QFileInfo(FileModel::instance().renamedFileName(index)).fileName());
	if (dialog.exec() != QDialog::Accepted)
		return;

	if (dialog.automaticRename())
		FileModel::instance().removeManualRenaming(index);
	else
		FileModel::instance().setManualRenaming(index, dir.absoluteFilePath(dialog.fileName()));
}

void WidgetSimple::changeEvent(QEvent *event) {
	if (event->type() == QEvent::LanguageChange) {
		// Operation combobox
		uiRetranslating = true;
		int oldOperationCurrentIndex = comboBoxOperation->currentIndex();
		retranslateUi(this);
		comboBoxOperation->setCurrentIndex(oldOperationCurrentIndex);
		uiRetranslating = false;

		refreshFileCount();
	} else
		QWidget::changeEvent(event);
}

void WidgetSimple::newProfile() {
	widgetExtensionPolicy->setExtensionPolicy(FilterModel::instance().extensionPolicy());
	widgetFilters->newProfile();
	widgetFinalizers->newProfile();
}

void WidgetSimple::filesDropDone() {
	int i = 0;
	foreach (int row, FileModel::instance().dropRows()) {
		QItemSelectionModel::SelectionFlags flags = QItemSelectionModel::Select | QItemSelectionModel::Rows;
		treeViewFiles->selectionModel()->select(FileModel::instance().index(row, 0), i ? flags : QItemSelectionModel::Clear | flags);
		i++;
	}
}

void WidgetSimple::on_actionSortByName_triggered() {
	FileModel::instance().sort(FileModel::SortByName);
}

void WidgetSimple::on_actionSortByModificationDate_triggered() {
	FileModel::instance().sort(FileModel::SortByModificationDate);
}

void WidgetSimple::on_actionRemoveSelectedFiles_triggered() {
	QModelIndexList list = treeViewFiles->selectionModel()->selectedRows();
	if (!list.count())
		return;

	if (QMessageBox::question(this, tr("Confirmation"), tr("Do you really want to remove this files?"),
							  QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
		return;

	QMap<int, int> rowsAndHeights;

	foreach (const QItemSelectionRange &range, treeViewFiles->selectionModel()->selection())
		rowsAndHeights.insert(range.top(), range.height());

	QList<int> rows = rowsAndHeights.keys();
	for (int i = rows.count() - 1; i >= 0; --i)
		FileModel::instance().removeRows(rows[i], rowsAndHeights[rows[i]], QModelIndex());

	if (!FileModel::instance().rowCount())
		stackedWidgetFiles->setCurrentWidget(pageNoFiles);
}

void WidgetSimple::on_actionAddFiles_triggered() {
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Pick some files"),
													  QDir::home().absolutePath());
    foreach (const QString &file, files)
		FileModel::instance().addFile(file);

	if (FileModel::instance().rowCount())
		stackedWidgetFiles->setCurrentWidget(pageFiles);
}

void WidgetSimple::contextMenuEvent(QContextMenuEvent *event) {
	QMenu popupMenu;
	popupMenu.addAction(actionAddFiles);
	if (treeViewFiles->selectionModel()->selectedRows().count()) {
		popupMenu.addAction(actionRemoveSelectedFiles);
		popupMenu.addSeparator();
		popupMenu.addAction(actionUpSelectedFiles);
		popupMenu.addAction(actionDownSelectedFiles);
	}

	popupMenu.exec(event->globalPos());
}

void WidgetSimple::treeViewFilesSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
	pushButtonRemoveFiles->setEnabled(treeViewFiles->selectionModel()->selectedRows().count());
	pushButtonUpFiles->setEnabled(treeViewFiles->selectionModel()->selectedRows().count());
	pushButtonDownFiles->setEnabled(treeViewFiles->selectionModel()->selectedRows().count());
}

void WidgetSimple::on_actionUpSelectedFiles_triggered() {
	QModelIndexList list = treeViewFiles->selectionModel()->selectedRows();
	if (list.count()) {
		FileModel::instance().upRows(list);
		filesDropDone();
	}
}

void WidgetSimple::on_actionDownSelectedFiles_triggered() {
	QModelIndexList list = treeViewFiles->selectionModel()->selectedRows();
	if (list.count()) {
		FileModel::instance().downRows(list);
		filesDropDone();
	}
}
