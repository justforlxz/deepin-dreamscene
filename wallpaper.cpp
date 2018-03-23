#include "wallpaper.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QApplication>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QDesktopWidget>
#include <QDebug>

Wallpaper::Wallpaper(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);

    registerDesktop();

    m_mpv = new MpvWidget(this);

    m_mpv->setGeometry(geometry());
    layout->addWidget(m_mpv);
    m_mpv->hide();

    m_mpv->setProperty("loop", true);

    connect(qApp->desktop(), &QDesktopWidget::resized, this, &Wallpaper::updateGeometry);
    QTimer::singleShot(1, this, &Wallpaper::updateGeometry);

    QTimer::singleShot(100, this, [=] {
        setFile("/home/haruyukilxz/Videos/一択彼女加藤恵.mov");
        play();
    });
}

void Wallpaper::setFile(const QString &path)
{
    m_mpv->show();
    m_mpv->command(QStringList() << "loadfile" << path);
    m_mpv->setProperty("pause", true);
}

void Wallpaper::setVolume(const qint32 volume)
{
    m_mpv->setProperty("volume", volume);
}

void Wallpaper::clear()
{
    stop();
    hide();
}

void Wallpaper::play()
{
    m_mpv->show();
    m_mpv->setProperty("pause", false);
}

void Wallpaper::pause()
{
    m_mpv->setProperty("pause", true);
}

void Wallpaper::stop()
{
    m_mpv->setProperty("stop", true);
}

void Wallpaper::registerDesktop()
{
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    QTimer::singleShot(1, this, [=] {
        show();
        lower();
    });
}

void Wallpaper::updateGeometry()
{
    QTimer::singleShot(100, this, [=] {
        const QRect &rec = qApp->desktop()->screenGeometry(qApp->desktop()->primaryScreen());
        setGeometry(rec);
        m_mpv->move(rect().topLeft());
        m_mpv->setFixedSize(size());
        lower();
    });
}
