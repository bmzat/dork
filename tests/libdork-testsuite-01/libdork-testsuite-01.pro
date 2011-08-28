#-------------------------------------------------
#
# Project created by QtCreator 2011-08-26T02:07:57
#
#-------------------------------------------------
include(../../dork.pri)
QT       += sql script testlib

QT       -= gui
DESTDIR =../../bin
TARGET = tst_repositorytest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../src/qdjango ../../src/dorkcore

LIBS += -L$$DESTDIR -ldorkcore
SOURCES += tst_repositorytest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
