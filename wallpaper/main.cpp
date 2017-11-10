#include <QObject>
#include <DApplication>
#include "wallpaper.h"
#include "dbuswallpaperservice.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    if (a.setSingleInstance("dde-wallpaper")) {
        a.setApplicationName("dde-wallpaper");
        a.setApplicationVersion("Version 0.1");

        Wallpaper *w = new Wallpaper;
        DBusWallpaperService *dbusInter = new DBusWallpaperService(w);
        Q_UNUSED(dbusInter);

        QDBusConnection::sessionBus().registerService("com.deepin.dde.Wallpaper");
        QDBusConnection::sessionBus().registerObject("/com/deepin/dde/Wallpaper", "com.deepin.dde.Wallpaper", w);

        QString envName("DDE_SESSION_PROCESS_COOKIE_ID");

        QByteArray cookie = qgetenv(envName.toUtf8().data());
        qunsetenv(envName.toUtf8().data());

        if (!cookie.isEmpty()) {
            QDBusInterface iface("com.deepin.SessionManager",
                                 "/com/deepin/SessionManager",
                                 "com.deepin.SessionManager",
                                 QDBusConnection::sessionBus());
            iface.asyncCall("Register", QString(cookie));
        }
    }

    return a.exec();
}


