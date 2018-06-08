DEFINES += QT_MESSAGELOGCONTEXT

HEADERS += \
            plugininterface.h \
            proxyinterface.h

INCLUDEPATH += $$PWD

isEmpty(PREFIX)
{
    PREFIX = /usr
}
