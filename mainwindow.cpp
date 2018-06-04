#include "mainwindow.h"
#include "backgroundview.h"
#include "packagemanager.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QQuickItem>

MainWindow::MainWindow(QWidget *parent)
    : DWindow(parent)
{
    PackageManager *packageManager = new PackageManager;;
    BackgroundView *backgroundView = new BackgroundView;
    backgroundView->show();
    backgroundView->lower();

    QQuickWidget *view = new QQuickWidget;
    view->setSource(QUrl("qrc:/window.qml"));

    view->rootContext()->setContextProperty("packageManager", packageManager);

    QObject *rootObject = qobject_cast<QObject*>(view->rootObject());
    connect(rootObject, SIGNAL(activated(QString)),
            packageManager, SLOT(setActivate(QString)));

    connect(packageManager, &PackageManager::requestSetItem,
            backgroundView, &BackgroundView::setContent);

    setContentWidget(view);
}
