#include "wallpaper.h"
#include <QVideoWidget>
#include <QFileDialog>
#include <QStandardPaths>

Wallpaper::Wallpaper(const QString path, QWidget *parent) : QWidget(parent)
{
    mainlayout = new QVBoxLayout(this);
    mainlayout->setMargin(0);
    mainlayout->setSpacing(0);
    QVideoWidget *videoWidget = new QVideoWidget;
    mainlayout->addWidget(videoWidget);
    mediaPlayer.setVideoOutput(videoWidget);
    setLayout(mainlayout);

    mediaPlayer.setMedia(QUrl("file://" + path));
    mediaPlayer.pause();
    videoWidget->show();
}

void Wallpaper::play()
{
    mediaPlayer.play();
    mediaPlayer.setVolume(0);
}
