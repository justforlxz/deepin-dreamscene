#include <QObject>
#include <DApplication>

#include "wallpaper.h"
#include "dbuswallpaperservice.h"
#include "settings.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("light");

    setlocale(LC_NUMERIC, "C");

    if (a.setSingleInstance("deepin-dreamscene")) {
        a.setApplicationName(QObject::tr("Deepin DreamScene"));
        a.setApplicationVersion("Version 0.1");

        Wallpaper *w = new Wallpaper;
        DBusWallpaperService *dbusInter = new DBusWallpaperService(w);
        Q_UNUSED(dbusInter);

        QDBusConnection::sessionBus().registerService("com.deepin.dde.DreamScene");
        QDBusConnection::sessionBus().registerObject("/com/deepin/dde/DreamScene", "com.deepin.dde.DreamScene", w);

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

#ifdef QT_DEBUG
        Settings *s = new Settings;
        s->show();
#endif
    }

    return a.exec();
}


