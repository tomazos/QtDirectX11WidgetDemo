// (C) 2011, Andrew Tomazos <andrew@tomazos.com>.

#include <QtGui/QApplication>
#include <QtCore/QDir>

#include "DXGI.h"

#include "Log.h"
#include "MainWindow.h"
#include "Engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Log log;

    MainWindow mainWindow;
    mainWindow.setLog(&log);
    mainWindow.show();

    log.log(QDir::currentPath());
    mainWindow.init();

    PEngine pEngine = Engine::create(&log, mainWindow.getEngineView());

    return a.exec();
}
