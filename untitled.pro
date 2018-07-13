#-------------------------------------------------
#
# Project created by QtCreator 2016-04-14T15:11:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    posix_qextserialport.cpp \
    qextserialbase.cpp \
    gps.cpp

HEADERS  += widget.h \
    posix_qextserialport.h \
    qextserialbase.h \
    gps.h

FORMS    += widget.ui

//RESOURCES += \
//    ../../12.qrc

//DISTFILES += \
//    ../../2016-05-10 16-11-02.jpg \
//    ../../2016-05-10 16-11-02.jpg

RESOURCES += \
    tupian.qrc
