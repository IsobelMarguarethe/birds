#-------------------------------------------------
#
# Project created by QtCreator 2016-11-18T08:28:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Birds
TEMPLATE = app


SOURCES += main.cpp\
    displaywindow.cpp \
    mainwindow.cpp \
    birdplayer.cpp \
    ThreeVector.cpp \
    bird.cpp \
    predator.cpp \
    prey.cpp \
    aviationsystem.cpp \
    obstacle.cpp

HEADERS  += displaywindow.h \
    mainwindow.h \
    birdplayer.h \
    ThreeVector.h \
    bird.h \
    predator.h \
    prey.h \
    aviationsystem.h \
    obstacle.h

FORMS    += displaywindow.ui \
    mainwindow.ui
    mainwindow.ui \

