#ifndef WALLPAPER_H
#define WALLPAPER_H

#include "wallpapermask.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <DVideoWidget>
#include <QFileSystemWatcher>
#include <QPropertyAnimation>

DWIDGET_USE_NAMESPACE

class Wallpaper : public QWidget
{
    Q_OBJECT
public:
    explicit Wallpaper(QWidget *parent = 0);

public slots:
    void setVideoFile(const QStringList &videolist, int volume, bool range = false);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void registerDesktop();

private slots:
    void onTimerOut();
    void onFolderChanged();

    void adjustGeometry();
private:
    bool m_isVideo;
    QPixmap m_pixmap;
    QStringList m_picList;
    QFileSystemWatcher *m_folderWatcher;
    QVBoxLayout *mainlayout;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *playlist;
    DVideoWidget *videoWidget;
    int m_index;
    QTimer *m_adjustTimer;
    WallpaperMask *m_label;
    QPropertyAnimation *redAnimation;
};

#endif // WALLPAPER_H
