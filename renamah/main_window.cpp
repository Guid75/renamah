#include <QTranslator>
#include <QSettings>
#include <QLibraryInfo>
#include <QFileDialog>

#include "plugin_manager.h"
#include "filter_model.h"
#include "processor.h"
#include "profile.h"
#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
	: actionGroupLanguages(0),
	  QMainWindow(parent) {
	setupUi(this);

	PluginManager::instance().load();

	tabWidgetMain->setCurrentWidget(tabSimple);

	connect(&Processor::instance(), SIGNAL(started()), this, SLOT(processorStarted()));

	widgetSimple->initAfterPluginLoaded();

	actionLanguage->setMenu(&menuLanguages);

	QSettings settings;
	QString currentLanguage = settings.value("general/language", "").toString();
	if (currentLanguage != "")
		installLanguage(currentLanguage);

	refreshLanguageActions();

	connect(&signalMapperLanguages, SIGNAL(mapped(const QString &)),
			this, SLOT(languageRequested(const QString &)));
}

void MainWindow::refreshLanguageActions() {
	if (actionGroupLanguages)
		delete actionGroupLanguages;
	actionGroupLanguages = new QActionGroup(this);
	menuLanguages.clear();

	QAction *actionToCheck = 0;
	QSettings settings;
	QString currentLanguage = settings.value("general/language", "").toString();

	// Get languages list
	foreach (const QFileInfo &fileInfo, QDir(QCoreApplication::applicationDirPath()).entryInfoList(QStringList() << "*.qm",
																								   QDir::Files)) {
		QString baseName = fileInfo.baseName();
		int p = baseName.indexOf("_");
		if (p > 0) {
			QString fileLanguage = baseName.mid(p + 1, baseName.length() - p - 1);
			QLocale locale(fileLanguage);
			QString language = QLocale::languageToString(locale.language());
			QString country = QLocale::countryToString(locale.country());
			QAction *action = menuLanguages.addAction(QString("%1 (%2)").arg(language).arg(country));
			if (fileLanguage == currentLanguage)
				actionToCheck = action;
			signalMapperLanguages.setMapping(action, fileLanguage);
			connect(action, SIGNAL(triggered()), &signalMapperLanguages, SLOT(map()));
			action->setCheckable(true);
			actionGroupLanguages->addAction(action);
		}
	}

	if (actionToCheck)
		actionToCheck->setChecked(true);
}

void MainWindow::processorStarted() {
	tabWidgetMain->setCurrentWidget(tabLastOperations);
}

void MainWindow::languageRequested(const QString &language) {
	installLanguage(language);

	QSettings settings;
	settings.setValue("general/language", language);
}

void MainWindow::changeEvent(QEvent *event) {
	if (event->type() == QEvent::LanguageChange) {
		retranslateUi(this);
	} else
		QWidget::changeEvent(event);
}

void MainWindow::installLanguage(const QString &language) {
	// Remove all existing translators
	foreach (QTranslator *translator, translators)
		qApp->removeTranslator(translator);
	translators.clear();

	// Install the Qt translator
	QTranslator *qtTranslator = new QTranslator;
	qtTranslator->load("qt_" + language,
					   QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(qtTranslator);

	// Install the main app translator
	QTranslator *translator = new QTranslator;
	translator->load("renamah_" + language,
					 QCoreApplication::applicationDirPath());
    qApp->installTranslator(translator);
	translators << translator;

	// Install all plugins translators
	foreach (const QString &fileName, PluginManager::instance().pluginFileNames()) {
		QFileInfo fileInfo(fileName);
		QString baseName = fileInfo.completeBaseName();
		QString qmFileName = fileInfo.absoluteDir().filePath(baseName) + "_" + language + ".qm";

		QTranslator *translator = new QTranslator;
		translator->load(qmFileName,
						 QCoreApplication::applicationDirPath());
		qApp->installTranslator(translator);
		translators << translator;
	}
}

void MainWindow::on_actionLoadProfile_triggered() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Choose a profile to load"),
													QDir::home().absolutePath());
	if (fileName == "")
		return;

	if (!Profile::load(fileName))
		return;

	widgetSimple->newProfile();
}

void MainWindow::on_actionSaveProfile_triggered() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a profile filename to save in"),
													QDir::home().absolutePath());
	if (fileName == "")
		return;

	Profile::save(fileName);
}