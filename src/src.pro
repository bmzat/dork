TEMPLATE = subdirs
include(../dork.pri)
CONFIG += ordered

SUBDIRS += qdjango dorkcore

dorkcore.depends += qdjango
