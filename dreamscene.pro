TEMPLATE = app

QT += gui x11extras widgets multimediawidgets multimedia
CONFIG += c++11 link_pkgconfig
PKGCONFIG += xcb xcb-ewmh dtkwidget dtkbase

SOURCES += main.cpp \
    wallpaper.cpp \
    settings.cpp \
    trayicon.cpp \
    Window/settingstitle.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    wallpaper.h \
    settings.h \
    trayicon.h \
    Window/settingstitle.h

RESOURCES += \
    resource.qrc
