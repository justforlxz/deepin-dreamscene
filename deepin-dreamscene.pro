TEMPLATE = app

QT += gui x11extras widgets dbus qml
CONFIG += c++11 link_pkgconfig
PKGCONFIG += xcb-ewmh dtkwidget
TARGET = deepin-dreamscene

SOURCES += main.cpp \
    packagemanager.cpp \
    backgroundview.cpp

HEADERS += \
    packagemanager.h \
    backgroundview.h \
    plugininterface.h \
    proxyinterface.h

RESOURCES += \
    deepin-dreamscene.qrc

target.path = /usr/bin/

DISTFILES += \
    com.deepin.dde.DreamScene.service

dbus_service.files += com.deepin.dde.DreamScene.service
dbus_service.path = /usr/share/dbus-1/services

include_file.files += plugininterface.h proxyinterface.h
include_file.path = /usr/include/deepin-dreamscene/

INSTALLS += target dbus_service include_file
