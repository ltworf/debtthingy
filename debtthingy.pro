#-------------------------------------------------
#
# Project created by QtCreator 2014-05-09T02:58:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = debtthingy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    personwidget.cpp

HEADERS  += mainwindow.h \
    personwidget.h

FORMS    += mainwindow.ui \
    personwidget.ui

CONFIG += mobility
MOBILITY = 

