#-------------------------------------------------
#
# Project created by QtCreator 2018-11-28T19:41:39
#
#-------------------------------------------------

QT       += core sql
QT       += network
CONFIG   += c++11
win32
{
    LIBS += -lole32
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    member.cpp \
    moderator.cpp \
    administrator.cpp \
    comment.cpp \
    post.cpp \
    usermanager.cpp \
    board.cpp \
    guid.cpp \
    forum.cpp \
    logindlg.cpp \
    infodlg.cpp \
    postdlg.cpp \
    editdlg.cpp \
    addcommentdlg.cpp \
    modifypostdlg.cpp \
    chooseboarddlg.cpp \
    registerdlg.cpp \
    anonymoususer.cpp \
    Socket.cpp

HEADERS  += mainwindow.h \
    user.h \
    member.h \
    moderator.h \
    administrator.h \
    comment.h \
    post.h \
    usermanager.h \
    board.h \
    guid.h \
    forum.h \
    logindlg.h \
    infodlg.h \
    postdlg.h \
    editdlg.h \
    addcommentdlg.h \
    modifypostdlg.h \
    chooseboarddlg.h \
    registerdlg.h \
    anonymoususer.h \
    Socket.h

FORMS    += mainwindow.ui \
    logindlg.ui \
    infodlg.ui \
    postdlg.ui \
    editdlg.ui \
    addcommentdlg.ui \
    modifypostdlg.ui \
    chooseboarddlg.ui \
    registerdlg.ui

RESOURCES += \
    src.qrc
