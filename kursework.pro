#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T09:59:19
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kursework
TEMPLATE = app

LIBS += -lglu32 -lopengl32


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp \
    particle.cpp

HEADERS  += mainwindow.h \
    widget.h \
    particle.h

FORMS    += mainwindow.ui

