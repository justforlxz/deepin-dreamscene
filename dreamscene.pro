TEMPLATE = app

QT += gui x11extras widgets multimediawidgets multimedia dbus
CONFIG += c++11 link_pkgconfig
PKGCONFIG += xcb xcb-ewmh dtkwidget dtkbase
TARGET = dde-wallpaper

SOURCES += main.cpp \
    wallpaper.cpp \
    dbuswallpaperservice.cpp \
    wallpapermask.cpp

HEADERS += \
    wallpaper.h \
    dbuswallpaperservice.h \
    wallpapermask.h

RESOURCES +=

target.path = /usr/bin/

DISTFILES += \
    com.deepin.dde.Wallpaper.service

dbus_service.files += com.deepin.dde.Wallpaper.service
dbus_service.path = /usr/share/dbus-1/services

INSTALLS += target dbus_service
