#-------------------------------------------------
#
# Project created by QtCreator 2011-08-26T02:07:57
#
#-------------------------------------------------
include(../../dork.pri)
QT       += sql script testlib

QT       -= gui
DESTDIR =../../bin
TARGET = dork-testsuite-01
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../src/qdjango ../../src/dorkcore

LIBS += -L$$DESTDIR -ldorkcore -lqdjango
SOURCES += tst_repositorytest.cpp tst_branchtest.cpp repotest.cpp main.cpp
HEADERS += tst_repositorytest.h repotest.h  tst_branchtest.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
