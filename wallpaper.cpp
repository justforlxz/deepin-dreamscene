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

Wallpaper::Wallpaper(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);

    videoWidget = new DVideoWidget;
    layout->addWidget(videoWidget);

    videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    mediaPlayer = new QMediaPlayer;
    playlist = new QMediaPlaylist(mediaPlayer);

    videoWidget->setSource(mediaPlayer);

    mediaPlayer->setPlaylist(playlist);

    mediaPlayer->pause();

    setGeometry(qApp->primaryScreen()->geometry());
    videoWidget->resize(size());

    connect(qApp->primaryScreen(), &QScreen::geometryChanged, [=] {
        setGeometry(qApp->primaryScreen()->geometry());
        videoWidget->resize(size());
        lower();
    });

    hide();
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

    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    show();
    lower();
}

void Wallpaper::clear()
{
    hide();
    mediaPlayer->stop();
    playlist->clear();
}
