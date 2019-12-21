QT += core sql
QT += network
QT -= gui

CONFIG += c++11
win32
{
    LIBS += -lole32
}

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myserver.cpp \
    mythread.cpp \
    mysql.cpp

HEADERS += \
    myserver.h \
    mythread.h \
    mysql.h
