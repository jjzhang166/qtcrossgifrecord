#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T12:52:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtCrossCamGif
TEMPLATE = app

#DEFINES += SRCDIR=\\\"$$PWD/\\\"
include(3rdparty/qtgifimage/src/gifimage/qtgifimage.pri)

win32:{
    RC_ICONS += camgif.ico
    RC_FILE += camClient.rc
}
SOURCES += main.cpp\
        ddcamgifwidget.cpp \
    frameless_helper.cpp \
    ddimagemanager.cpp

HEADERS  += ddcamgifwidget.h \
    frameless_helper.h \
    ddimagemanager.h

FORMS    += ddcamgifwidget.ui

RESOURCES += \
    camgif.qrc

LIBS += -lUser32
