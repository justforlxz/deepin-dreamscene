TEMPLATE = app

QT += gui x11extras widgets multimediawidgets multimedia dbus
CONFIG += c++11 link_pkgconfig
PKGCONFIG += xcb xcb-ewmh dtkwidget dtkbase

SOURCES += main.cpp \
    wallpaper.cpp \
    dbuswallpaperservice.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    wallpaper.h \
    dbuswallpaperservice.h

RESOURCES += \
    resource.qrc
