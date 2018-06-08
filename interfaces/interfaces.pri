DEFINES += QT_MESSAGELOGCONTEXT

HEADERS += \
            $$PWD/plugininterface.h \
            $$PWD/proxyinterface.h

INCLUDEPATH += $$PWD

isEmpty(PREFIX)
{
    PREFIX = /usr
}
