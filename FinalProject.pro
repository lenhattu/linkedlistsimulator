#-------------------------------------------------
#
# Project created by QtCreator 2015-04-10T23:56:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinalProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    node.cpp \
    sllist.cpp


HEADERS  += mainwindow.h \
    node.h \
    sllist.h

FORMS    += mainwindow.ui

RESOURCES += \
    myres.qrc
