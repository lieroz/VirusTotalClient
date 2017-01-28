#-------------------------------------------------
#
# Project created by QtCreator 2017-01-23T22:52:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VirusTotalClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networkmanager.cpp \
    filebrowser.cpp \
    commentdialog.cpp

HEADERS  += mainwindow.h \
    networkmanager.h \
    responses.h \
    status_codes.h \
    program_exceptions.h \
    filebrowser.h \
    commentdialog.h

FORMS    += mainwindow.ui \
    filebrowser.ui \
    commentdialog.ui
