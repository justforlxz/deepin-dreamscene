#include "wallpaper.h"
#include <QVideoWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMediaPlaylist>
#include <QApplication>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <DVideoWidget>

DWIDGET_USE_NAMESPACE

Wallpaper::Wallpaper(QWidget *parent) : QWidget(parent)
{
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    DVideoWidget *videoWidget = new DVideoWidget(this);

    videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    mediaPlayer = new QMediaPlayer;
    playlist = new QMediaPlaylist(mediaPlayer);

    videoWidget->setSource(mediaPlayer);

    mediaPlayer->setPlaylist(playlist);

    mediaPlayer->pause();
    videoWidget->show();

    setGeometry(qApp->primaryScreen()->geometry());
    videoWidget->resize(size());
    lower();

    connect(qApp->primaryScreen(), &QScreen::geometryChanged, [=] {
        setGeometry(qApp->primaryScreen()->geometry());
        videoWidget->resize(size());
        lower();
    });
}

void Wallpaper::setVideoFile(const QStringList &videolist, int volume, bool range)
{
    clear();

    for (const QString &file : videolist) {
        if (QFile::exists(file))
            playlist->addMedia(QUrl("file://" +  file));
        else
            continue;
    }

    if (range)
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    else
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

    mediaPlayer->play();
    mediaPlayer->setVolume(volume);
    show();
}

void Wallpaper::clear()
{
    hide();
    mediaPlayer->stop();
    playlist->clear();
}