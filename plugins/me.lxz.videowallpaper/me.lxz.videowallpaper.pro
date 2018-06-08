#-------------------------------------------------
#
# Project created by QtCreator 2018-06-08T11:36:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
CONFIG += plugin c++11 link_pkgcoonfig
TARGET          = $$qtLibraryTarget(videowallpaper)
DESTDIR          = $$_PRO_FILE_PWD_/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../../interfaces/interfaces.pri)

SOURCES += \
        wallpaper.cpp \
    wallpaperplugins.cpp

HEADERS += \
        wallpaper.h \
    wallpaperplugins.h

target.path = $${PREFIX}/lib/deepin-dreamscene/plugins/me.lxz.videowallpaper/

file.path = $${PREFIX}/lib/deepin-dreamscene/plugins/me.lxz.videowallpaper/
file.files += package.json

preview.path = $${PREFIX}/lib/deepin-dreamscene/plugins/me.lxz.videowallpaper/
preview.files += preview.jpg

INSTALLS += target file

