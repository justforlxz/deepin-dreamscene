#include "trayicon.h"
#include <QApplication>
#include <QDebug>

TrayIcon::TrayIcon(QObject *parent) :
    QObject(parent),
    trayIcon(new QSystemTrayIcon(this))
{
    QIcon icon = QIcon(":/logo.png");
     trayIcon->setIcon(icon);
     trayIcon->setToolTip(tr("子曰USay"));
     trayIcon->show();
//     trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);

     connect(trayIcon, &QSystemTrayIcon::activated, this, &TrayIcon::trayiconActivated);

     showAction = new QAction(tr("show"), this);
     connect(showAction, &QAction::triggered, this, &TrayIcon::show);

     quitAction = new QAction(tr("退出 (&Q)"), this);
     connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

     trayIconMenu = new QMenu;
     trayIconMenu->addAction(showAction);
     trayIconMenu->addAction(quitAction);
     trayIcon->setContextMenu(trayIconMenu);
}

void TrayIcon::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:;
        //单击托盘图标
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        emit show();
        break;
    default:
        break;
    }
}
