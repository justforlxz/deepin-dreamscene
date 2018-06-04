#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include "proxyinterface.h"

#include <QWidget>

class PluginInterface
{
public:
    virtual void init(ProxyInterface * const inter) = 0;

    virtual QWidget *contentWidget() = 0;
    virtual QString *name() = 0;
    virtual QString *version() = 0;
};

QT_BEGIN_NAMESPACE
#define ModuleInterface_iid "com.deepin.dreamscene.PluginsItemInterface"

Q_DECLARE_INTERFACE(PluginInterface, ModuleInterface_iid)
QT_END_NAMESPACE

#endif // PLUGININTERFACE_H
