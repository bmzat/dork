#-------------------------------------------------
#
# Project created by QtCreator 2011-08-25T23:52:44
#
#-------------------------------------------------

QT       += network sql script

QT       -= gui

DLLDESTDIR = ../../bin

TARGET = dorkcore
TEMPLATE = lib

DEFINES += LIBDORK_LIBRARY

SOURCES += repository.cpp \
    blob.cpp \
    branch.cpp \
    dirtree.cpp \
    commit.cpp

HEADERS += repository.h\
        libdork_global.h \
    blob.h \
    branch.h \
    dirtree.h \
    commit.h

LIBS += -L$$DESTDIR -lqdjango
INCLUDEPATH += ../qdjango

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0A10FC7
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = libdork.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    dorkcore.qrc

OTHER_FILES += \
    resources/repo.js
