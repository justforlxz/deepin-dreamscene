TEMPLATE = app

QT += gui x11extras widgets dbus qml quickwidgets
CONFIG += c++11 link_pkgconfig
PKGCONFIG += xcb-ewmh dtkwidget
TARGET = deepin-dreamscene
DESTDIR    = $$_PRO_FILE_PWD_/../

include(../interfaces/interfaces.pri)

SOURCES += main.cpp \
    packagemanager.cpp \
    backgroundview.cpp \
    mainwindow.cpp

HEADERS += \
    packagemanager.h \
    backgroundview.h \
    mainwindow.h

RESOURCES += \
    deepin-dreamscene.qrc

target.path = $$PREFIX/bin/

DISTFILES += \
    com.deepin.dde.DreamScene.service

dbus_service.files += com.deepin.dde.DreamScene.service
dbus_service.path = $$PREFIX/share/dbus-1/services

include_file.files += plugininterface.h proxyinterface.h
include_file.path = $$PREFIX/include/deepin-dreamscene/

INSTALLS += target dbus_service include_file
