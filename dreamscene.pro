TEMPLATE = app

QT += gui x11extras widgets multimediawidgets multimedia
CONFIG += c++11 link_pkgconfig
PKGCONFIG += xcb xcb-ewmh

SOURCES += main.cpp \
    wallpaper.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    wallpaper.h
