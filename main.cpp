#include <QGuiApplication>

#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <QQuickItem>
#include "QQmlContext"

#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

#include <sys/types.h>    // defines special types
#include <pwd.h>    // defines the passwd structure
#include <unistd.h>//header for getuid system call

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QQuickView *w;

    w = new QQuickView;
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, w->winId(), 1, atoms);

    struct passwd *user;
    user = getpwuid(getuid());

    QString videopath = QString(user->pw_dir) + "/.local/mkacg/main.qml";

    w->setSource(QUrl(videopath));
    w->setGeometry(qApp->primaryScreen()->geometry());
    w->show();
    w->lower();

    QObject::connect(qApp->primaryScreen(), &QScreen::geometryChanged, [=] {
        w->setGeometry(qApp->primaryScreen()->geometry());
        w->lower();
    });



    return a.exec();
}
