#include "mainwindow.h"
#include "backgroundview.h"
#include "packagemanager.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QQuickItem>
#include <DPlatformWindowHandle>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    DPlatformWindowHandle::enableDXcbForWindow(this, true);
    DPlatformWindowHandle *handle = new DPlatformWindowHandle(this, this);
    handle->setEnableBlurWindow(false);

//    setAttribute(Qt::WA_TranslucentBackground);

    PackageManager *packageManager = new PackageManager;;
    BackgroundView *backgroundView = new BackgroundView;
    backgroundView->show();
    backgroundView->lower();

    QQuickWidget *view = new QQuickWidget;
    view->setAttribute(Qt::WA_TranslucentBackground, true);
//    view->setAttribute(Qt::WA_AlwaysStackOnTop, true);
//    view->setClearColor(Qt::transparent);

    view->rootContext()->setContextProperty("packageManager", packageManager);
    view->setSource(QUrl("qrc:/window.qml"));

    QObject *rootObject = qobject_cast<QObject*>(view->rootObject());

    if (rootObject) {
        connect(rootObject, SIGNAL(activated(QString)),
                packageManager, SLOT(setActivate(QString)));
    }

    connect(packageManager, &PackageManager::requestSetItem,
            backgroundView, &BackgroundView::setContent);

    setCentralWidget(view);
}
