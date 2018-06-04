#include <QObject>
#include <DApplication>

#include "backgroundview.h"
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

    BackgroundView view;
    view.show();
    view.lower();

    engine.rootContext()->setContextProperty("packageManager", &packageManager);
    engine.load("qrc:/window.qml");

    QObject *rootObject = engine.rootObjects().first();
    QObject::connect(rootObject, SIGNAL(activated(QString)),
                      &packageManager, SLOT(setActivate(QString)));

    QObject::connect(&packageManager, &PackageManager::requestSetItem,
                     &view, &BackgroundView::setContent);

    return a.exec();
}


