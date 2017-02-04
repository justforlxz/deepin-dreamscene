#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = 0);

signals:
    void show();

private slots:
    void trayiconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QSystemTrayIcon *trayIcon;
    QAction *showAction;
    QAction *quitAction;
    QMenu   *trayIconMenu;
};

#endif // TRAYICON_H
