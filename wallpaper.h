#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMediaPlayer>

class Wallpaper : public QWidget
{
    Q_OBJECT
public:
    explicit Wallpaper(const QString path, QWidget *parent = 0);
    void play();

private:
    QVBoxLayout *mainlayout;
    QMediaPlayer mediaPlayer;
};

#endif // WALLPAPER_H
