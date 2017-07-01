#include "dbuswallpaperservice.h"
#include "wallpaper.h"

DBusWallpaperService::DBusWallpaperService(Wallpaper *parent)
    : QDBusAbstractAdaptor(parent),
      m_parent(parent)
{

}

Wallpaper *DBusWallpaperService::parent() const
{
    return m_parent;
}

void DBusWallpaperService::setVideoFile(const QStringList &videolist, int volume, bool range)
{
    m_parent->setVideoFile(videolist, volume, range);
}

void DBusWallpaperService::clear()
{
    m_parent->clear();
}
