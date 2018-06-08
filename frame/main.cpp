#include <QObject>
#include <DApplication>
#include <DWidgetUtil>

#include "mainwindow.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("light");

    MainWindow mw;
    mw.show();
    moveToCenter(&mw);

    return a.exec();
}


