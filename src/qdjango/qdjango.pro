#-------------------------------------------------
#
# Project created by QtCreator 2011-08-25T23:52:44
#
#-------------------------------------------------

QT       += network sql script

QT       -= gui

DLLDESTDIR = ../../bin

TARGET = qdjango
TEMPLATE = lib

DEFINES += QDJANGO_LIBRARY



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

HEADERS += \
    QDjangoWhere.h \
    QDjangoScript_p.h \
    QDjangoScript.h \
    QDjangoQuerySet_p.h \
    QDjangoQuerySet.h \
    QDjangoModel.h \
    QDjangoHttpServer_p.h \
    QDjangoHttpServer.h \
    QDjangoHttpResponse_p.h \
    QDjangoHttpResponse.h \
    QDjangoHttpRequest_p.h \
    QDjangoHttpRequest.h \
    QDjangoHttpController.h \
    QDjango_p.h \
    QDjango.h

SOURCES += \
    QDjangoWhere.cpp \
    QDjangoScript.cpp \
    QDjangoQuerySet.cpp \
    QDjangoModel.cpp \
    QDjangoHttpServer.cpp \
    QDjangoHttpResponse.cpp \
    QDjangoHttpRequest.cpp \
    QDjangoHttpController.cpp \
    QDjango.cpp
