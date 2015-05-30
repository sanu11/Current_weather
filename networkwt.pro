#-------------------------------------------------
#
# Project created by QtCreator 2014-12-28T14:06:07
#
#-------------------------------------------------

QT       += core gui

QT       -= gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = networkwt

CONFIG   += console
CONFIG   -= app_bundle
CONFIG +=static
QT += network
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \

HEADERS  += mainwindow.h \

FORMS    += mainwindow.ui



