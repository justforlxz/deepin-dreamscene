#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include "proxyinterface.h"

#include <QWidget>

class PluginInterface
{
public:
    PluginInterface() {}

    virtual void init(ProxyInterface * const inter) = 0;

    virtual QWidget *contentWidget() = 0;
    virtual QString *name() = 0;
    virtual QString *version() = 0;
};

#endif // PLUGININTERFACE_H
