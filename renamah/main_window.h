#include <QMenu>
#include <QSignalMapper>
#include <QTranslator>
#include <QActionGroup>

#include "ui_main_window.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
     Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);

protected:
	void changeEvent(QEvent *event);

private:
	QMenu menuLanguages;
	QActionGroup *actionGroupLanguages;
	QSignalMapper signalMapperLanguages;
	QList<QTranslator*> translators;

	void refreshLanguageActions();

	void installLanguage(const QString &language);

private slots:
	void processorStarted();
	void languageRequested(const QString &language);
	void on_actionLoadProfile_triggered();
	void on_actionSaveProfile_triggered();
};
