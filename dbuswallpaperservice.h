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
    void setVideoFile(const QStringList &videolist, int volume = 0, bool range = false);
    void clear();

private:
    Wallpaper *m_parent;
};

#endif // DBUSWALLPAPERSERVICE_H
