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

void DBusWallpaperService::setFolder(const QStringList &list, const bool isVideo)
{
    m_parent->setFolder(list, isVideo);
}

void DBusWallpaperService::setVolume(const qint32 volume)
{
    m_parent->setVolume(volume);
}

void DBusWallpaperService::setInterval(const qint32 interval)
{
    m_parent->setInterval(interval);
}

void DBusWallpaperService::clear()
{
    m_parent->clear();
}

void DBusWallpaperService::play()
{
    m_parent->play();
}

void DBusWallpaperService::pause()
{
    m_parent->pause();
}

void DBusWallpaperService::stop()
{
    m_parent->stop();
}
