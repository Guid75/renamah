#include <QMessageBox>
#include <QMouseEvent>
#include <QHeaderView>
#include <QMetaProperty>

#include "modifier_delegate.h"
#include "widget_modifiers.h"

WidgetModifiers::WidgetModifiers(QWidget *parent)
	: QWidget(parent),
	  _modifierManager(0),
	  _modifierModel(0) {
	setupUi(this);

	connect(&signalMapperAddModifier, SIGNAL(mapped(const QString &)),
			this, SLOT(addModifier(const QString &)));

	pushButtonAdd->setMenu(&menuAddModifier);
	connect(&menuAddModifier, SIGNAL(aboutToShow()), this, SLOT(aboutToShowAddModifierMenu()));

	treeView->setItemDelegate(new ModifierDelegate);

	labelAddModifier->installEventFilter(this);
	treeView->viewport()->installEventFilter(this);
	treeView->installEventFilter(this);
}

void WidgetModifiers::init(ModifierManager *modifierManager, ModifierModel &modifierModel) {
	_modifierManager = modifierManager;
	_modifierModel = &modifierModel;

	retranslate();

	treeView->setModel(_modifierModel);

	connect(_modifierModel, SIGNAL(rowsInserted(const QModelIndex &, int, int)),
			this, SLOT(modifiersInserted(const QModelIndex &, int, int)));

	treeView->header()->setResizeMode(0, QHeaderView::ResizeToContents);
	treeView->header()->setResizeMode(1, QHeaderView::ResizeToContents);
	connect(treeView->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)),
			this, SLOT(currentModifierChanged(const QModelIndex &, const QModelIndex &)));

	currentModifierChanged(QModelIndex(), QModelIndex());
}

void WidgetModifiers::retranslate() {
	labelAddModifier->setText(tr("Add a new %1").arg(_modifierManager->modifierTypeName()));

	core::Modifier *modifier = currentModifier();
	if (!modifier)
		return;

	core::ModifierFactory *factory = modifier->factory();

	labelModifierCaption->setText(factory->info().caption());
	labelModifierDescription->setText(factory->info().description());
}

void WidgetModifiers::on_pushButtonRemove_clicked() {
	QModelIndex index = treeView->currentIndex();
	if (!index.isValid())
		return;

	_modifierModel->removeModifier(index);
}

void WidgetModifiers::on_pushButtonUp_clicked() {
	QModelIndex index = treeView->currentIndex();
	if (!index.isValid())
		return;

	if (!index.row())
		return;

	_modifierModel->moveModifier(index.row(), index.row() - 1);
}

void WidgetModifiers::on_pushButtonDown_clicked() {
	QModelIndex index = treeView->currentIndex();
	if (!index.isValid())
		return;

	if (index.row() == _modifierModel->rowCount() - 1)
		return;

	_modifierModel->moveModifier(index.row(), index.row() + 1);
}

void WidgetModifiers::aboutToShowAddModifierMenu() {
	menuAddModifier.clear();

	foreach (core::ModifierFactory *factory, _modifierManager->factories())
	{
		QAction *action = menuAddModifier.addAction(factory->info().caption() + " (" + factory->info().description() + ")");
		connect(action, SIGNAL(triggered()), &signalMapperAddModifier, SLOT(map()));
		signalMapperAddModifier.setMapping(action, factory->info().name());
	}
}

void WidgetModifiers::addModifier(const QString &factoryName) {
	core::ModifierFactory *factory = _modifierManager->factoryByName(factoryName);
	Q_ASSERT_X(factory, "WidgetModifiers::addModifierClicked()", "<factoryName> seems to have no factory correspondant");

	_modifierModel->addModifier(factory->makeModifier());
	stackedWidgetConfiguration->setCurrentWidget(pageConfiguration);
}

void WidgetModifiers::currentModifierChanged(const QModelIndex &current, const QModelIndex &previous) {
	if (previous.isValid())
	{
		core::Modifier *previousModifier = _modifierModel->modifier(previous);
		core::ModifierFactory *previousFactory = previousModifier->factory();
		if (_configWidget)
		{
			previousFactory->deleteConfigurationWidget(_configWidget);
			_configWidget = 0;
		}
	}

	if (!current.isValid())
	{
		stackedWidgetConfiguration->setCurrentWidget(pageNoModifiers);
		currentModifierChanged(0);
		return;
	}

	stackedWidgetConfiguration->setCurrentWidget(pageConfiguration);

	core::Modifier *modifier = _modifierModel->modifier(current);
	core::ModifierFactory *factory = modifier->factory();

	_configWidget = modifier->factory()->makeConfigurationWidget(modifier);
	if (_configWidget)
	{
		setConfigWidget(_configWidget);

		frameConfiguration->setVisible(true);
		labelModifierCaption->setText(factory->info().caption());
		labelModifierDescription->setText(factory->info().description());

		connect(modifier, SIGNAL(settingsChanged()), this, SLOT(widgetModifierChanged()));
	}

	currentModifierChanged(modifier);
}

bool WidgetModifiers::eventFilter(QObject *obj, QEvent *ev) {
	if (obj == labelAddModifier && ev->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *event = static_cast<QMouseEvent*>(ev);
		menuAddModifier.popup(event->globalPos());
	} else if (obj == treeView->viewport() && ev->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *event = static_cast<QMouseEvent*>(ev);
		QPoint p = event->pos();
		QModelIndex index = treeView->indexAt(p);
		if (index.column() == ModifierModel::colMode)
		{
			if (modifierStateRect(index).contains(p))
				_modifierModel->toggleModifierState(_modifierModel->modifier(index));
			else
			{
				if (modifierOnlyRect(index).contains(p))
					_modifierModel->toggleExclusiveState(_modifierModel->modifier(index));
			}
		}
	} else if (obj == treeView && ev->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(ev);
		if (keyEvent->key() == Qt::Key_Delete)
		{
			on_pushButtonRemove_clicked();
		}
	}
	return QWidget::eventFilter(obj, ev);
}

QRect WidgetModifiers::modifierStateRect(const QModelIndex &index) const {
	QRect indexRect = treeView->visualRect(index);

	QRect res(indexRect.left(), indexRect.top(), 16, 16);

	if (indexRect.width() > 32)
		res.translate((indexRect.width() - 32) / 2, 0);

	if (indexRect.height() > 16)
		res.translate(0, (indexRect.height() - 16) / 2);

	return res;
}

QRect WidgetModifiers::modifierOnlyRect(const QModelIndex &index) const {
	QRect indexRect = treeView->visualRect(index);

	QRect res(indexRect.left() + 16, indexRect.top(), 16, 16);

	if (indexRect.width() > 32)
		res.translate((indexRect.width() - 32) / 2, 0);

	if (indexRect.height() > 16)
		res.translate(0, (indexRect.height() - 16) / 2);

	return res;
}

void WidgetModifiers::widgetModifierChanged() {
	if (treeView->currentIndex().isValid())
	{
		_modifierModel->refreshLayout();
		treeView->update(treeView->currentIndex());
	}
}

core::Modifier *WidgetModifiers::currentModifier() const {
	return _modifierModel->modifier(treeView->currentIndex());
}

void WidgetModifiers::changeEvent(QEvent *event) {
	if (event->type() == QEvent::LanguageChange) {
		retranslateUi(this);
		retranslate();
	} else
		QWidget::changeEvent(event);
}

void WidgetModifiers::newProfile() {
	if (_modifierModel->rowCount())
		treeView->setCurrentIndex(_modifierModel->index(0, 0));
}

void WidgetModifiers::modifiersInserted(const QModelIndex &parent, int start, int end) {
	treeView->setCurrentIndex(_modifierModel->index(start));
}
