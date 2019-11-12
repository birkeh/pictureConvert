/*!
 \file main.cpp

*/

#include "cmainwindow.h"

#include <QApplication>

#include <QFile>
#include <QTextStream>
#include <QSettings>

#include "csplashscreen.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	a.setApplicationVersion(APP_VERSION);
	a.setApplicationDisplayName("pictureConvert");
	a.setOrganizationName("WIN-DESIGN");
	a.setOrganizationDomain("windesign.at");
	a.setApplicationName("pictureConvert");

	QSettings		settings;

	QFile f(":qdarkstyle/style.qss");
	if (!f.exists())
	{
		printf("Unable to set stylesheet, file not found\n");
	}
	else
	{
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		a.setStyleSheet(ts.readAll());
	}

	QPixmap			pixmap(":/images/splash.png");
	QFont			splashFont;
	cSplashScreen*	lpSplash	= new cSplashScreen(pixmap, splashFont);

	lpSplash->show();
	a.processEvents();

	lpSplash->showStatusMessage(QObject::tr("<center>initializing...</denter>"));

	cMainWindow w(lpSplash);

	if(settings.value("main/maximized").toBool())
		w.showMaximized();
	else
		w.show();

	lpSplash->finish(&w);
	delete lpSplash;

	return a.exec();
}
