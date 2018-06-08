#ifndef WALLPAPERPLUGINS_H
#define WALLPAPERPLUGINS_H

#include "plugininterface.h"
#include "wallpaper.h"

#include <QObject>

class WallpaperPlugins : public QObject, PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dreamscene.PluginInterface")
public:
    explicit WallpaperPlugins(QObject *parent = nullptr);

protected:
    void init(ProxyInterface * const inter);
    QWidget *contentWidget();
    const QString name() const;
    const QString version() const;

private:
    Wallpaper *m_wallpaper;
};

#endif // WALLPAPERPLUGINS_H
