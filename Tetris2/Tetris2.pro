#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T17:06:44
#
#-------------------------------------------------

QT       += core gui\
            multimedia\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetris2
TEMPLATE = app


SOURCES += main.cpp\
    logindia.cpp \
    connectdia.cpp \
    singaldia.cpp \
    tboard.cpp \
    tetris.cpp \
    doubledia.cpp

HEADERS  += \
    logindia.h \
    connectdia.h \
    singaldia.h \
    tboard.h \
    tetris.h \
    doubledia.h

FORMS    += \
    logindia.ui \
    connectdia.ui \
    singaldia.ui \
    doubledia.ui

RESOURCES += \
    res.qrc
CONFIG +=c++11
