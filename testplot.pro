#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T02:16:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testplot
TEMPLATE = app
CONFIG += c++11 qwt


SOURCES += main.cpp\
        mainwindow.cpp \
         calculator.cpp \
    plotwidget.cpp

HEADERS  += mainwindow.h \
             calculator.h \
    plotwidget.h

FORMS    += mainwindow.ui
