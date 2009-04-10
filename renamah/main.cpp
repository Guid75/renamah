#include <QApplication>

#include "main_window.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);

	 app.setOrganizationName("GuidSofts");
	 app.setApplicationName("Renamah");
	 app.setApplicationVersion("0.01a");

	 MainWindow mainWindow;
     mainWindow.show();

     return app.exec();
}
