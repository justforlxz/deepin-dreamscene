#include "wallpaper.h"
#include <QVideoWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMediaPlaylist>

Wallpaper::Wallpaper(const QString path, QWidget *parent) : QWidget(parent)
{
    mainlayout = new QVBoxLayout(this);
    mainlayout->setMargin(0);
    mainlayout->setSpacing(0);
    QVideoWidget *videoWidget = new QVideoWidget;
    videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    mainlayout->addWidget(videoWidget, 0, Qt::AlignCenter);
    mediaPlayer.setVideoOutput(videoWidget);

    setLayout(mainlayout);

    QMediaPlaylist *playlist = new QMediaPlaylist(&mediaPlayer);
    playlist->addMedia(QUrl("file://" +  path));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaPlayer.setPlaylist(playlist);
    mediaPlayer.pause();

    videoWidget->show();
}

void Wallpaper::play()
{
    mediaPlayer.play();
    mediaPlayer.setVolume(0);
}
