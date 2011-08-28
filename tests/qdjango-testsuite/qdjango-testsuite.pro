#-------------------------------------------------
#
# Project created by QtCreator 2011-08-26T02:07:57
#
#-------------------------------------------------

include(../../dork.pri)
QT       += sql script testlib network

QT       -= gui
DESTDIR =../../bin
TARGET = tst_qdjango
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L$$DESTDIR -lqdjango
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += ../../src/qdjango

OTHER_FILES += \
    main.js

HEADERS += \
    shares_tests.h \
    shares_models.h \
    script.h \
    main.h \
    http.h \
    auth_tests.h \
    auth_models.h

SOURCES += \
    shares_tests.cpp \
    shares_models.cpp \
    script.cpp \
    main.cpp \
    http.cpp \
    auth_tests.cpp \
    auth_models.cpp

EXTRA_BINFILES = $${OTHER_FILES}

linux-g++{
    for(FILE,EXTRA_BINFILES){
        QMAKE_POST_LINK += $$quote(cp $${FILE} $${DESTDIR}$$escape_expand(\n\t))
    }
}

win32 {
    #...
    EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
    EXTRA_BINFILES_WIN ~= s,/,\\,g
        DESTDIR_WIN = $${DESTDIR}
    DESTDIR_WIN ~= s,/,\\,g
    for(FILE,EXTRA_BINFILES_WIN){
                QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\n\t))
    }
}
