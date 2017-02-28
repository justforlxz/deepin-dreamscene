#include <QObject>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <DApplication>
#include "wallpaper.h"
#include "settings.h"
#include "trayicon.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    a.setApplicationName("DDE Dream Scene");
    a.setApplicationVersion("Version 0.1");

    TrayIcon *t = new TrayIcon;
    Settings * s = new Settings;
    QObject::connect(t, &TrayIcon::show, s, &Settings::show);

    QCommandLineOption videopath("path", "set video path", "");
    videopath.setValueName("path");

    QCommandLineParser parser;

    parser.setApplicationDescription("Dream Scene");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(videopath);
    parser.process(a);

    if (parser.isSet(videopath)) {
        Wallpaper *w = new Wallpaper(parser.value(videopath));

        xcb_ewmh_connection_t m_ewmh_connection;
        xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
        xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

        xcb_atom_t atoms[1];
        atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
        xcb_ewmh_set_wm_window_type(&m_ewmh_connection, w->winId(), 1, atoms);

        w->setGeometry(qApp->primaryScreen()->geometry());
        w->show();
        w->lower();
        w->play();

        QObject::connect(qApp->primaryScreen(), &QScreen::geometryChanged, [=] {
            w->setGeometry(qApp->primaryScreen()->geometry());
            w->lower();
        });
    }

    return a.exec();
}
