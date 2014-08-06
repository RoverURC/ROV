#-------------------------------------------------
#
# Project created by QtCreator 2014-08-06T14:31:45
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = ROV_Console
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    rov.cpp


HEADERS += \
    rov.h


include(qextserialport/src/qextserialport.pri)


