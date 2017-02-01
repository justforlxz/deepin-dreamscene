TEMPLATE = app

QT += qml quick x11extras widgets
CONFIG += c++11 link_pkgconfig
PKGCONFIG += xcb xcb-ewmh

SOURCES += main.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS +=
