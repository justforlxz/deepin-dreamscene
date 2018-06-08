#include "wallpaperplugins.h"

WallpaperPlugins::WallpaperPlugins(QObject *parent) : QObject(parent)
{

}

void WallpaperPlugins::init(ProxyInterface * const inter)
{
    m_wallpaper = new Wallpaper;
}

QWidget *WallpaperPlugins::contentWidget()
{
    return m_wallpaper;
}

const QString WallpaperPlugins::name() const
{
    return QString("me.lxz.videowallpaper");
}

const QString WallpaperPlugins::version() const
{
    return QString("1.0");
}

void WallpaperPlugins::showSetting()
{

}
