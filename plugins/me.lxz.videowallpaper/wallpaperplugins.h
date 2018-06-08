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
    void init(ProxyInterface * const inter) Q_DECL_OVERRIDE;
    QWidget *contentWidget() Q_DECL_OVERRIDE;
    const QString name() const Q_DECL_OVERRIDE;
    const QString version() const Q_DECL_OVERRIDE;
    void showSetting() Q_DECL_OVERRIDE;

private:
    Wallpaper *m_wallpaper;
};

#endif // WALLPAPERPLUGINS_H
