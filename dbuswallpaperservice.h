#ifndef DBUSWALLPAPERSERVICE_H
#define DBUSWALLPAPERSERVICE_H

#include <QObject>
#include <QtDBus/QtDBus>
#include "wallpaper.h"

class Wallpaper;
class DBusWallpaperService : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.dde.Wallpaper")
public:
    explicit DBusWallpaperService(Wallpaper *parent);

    inline Wallpaper *parent() const;

public slots:
    void setFolder(const QStringList &list, const bool isVideo);
    void setVolume(const qint32 volume);
    void setInterval(const qint32 interval);
    void clear();
    void play();
    void pause();
    void stop();

private:
    Wallpaper *m_parent;
};

#endif // DBUSWALLPAPERSERVICE_H
