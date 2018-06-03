#include <QObject>
#include <DApplication>

#include "packagemanager.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("light");

    QQmlApplicationEngine engine;
    PackageManager packageManager;

    engine.rootContext()->setContextProperty("packageManager", &packageManager);
    engine.load("qrc:/window.qml");

    return a.exec();
}


