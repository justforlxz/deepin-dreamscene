TEMPLATE = subdirs
SUBDIRS += frame plugins

isEmpty(PREFIX) {
    PREFIX = /usr
}
