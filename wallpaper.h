#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <DVideoWidget>

DWIDGET_USE_NAMESPACE

class Wallpaper : public QWidget
{
    Q_OBJECT
public:
    explicit Wallpaper(QWidget *parent = 0);

public slots:
    void setVideoFile(const QStringList &videolist, int volume, bool range = false);
    void clear();

private:
    QVBoxLayout *mainlayout;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *playlist;
    DVideoWidget *videoWidget;
};

#endif // WALLPAPER_H
