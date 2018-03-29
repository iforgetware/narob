#-------------------------------------------------
#
# Project created by QtCreator 2018-01-14T09:34:22
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = narob-core
TEMPLATE = lib
CONFIG += lib c++11

DEFINES += NAROBCORE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    databasemanager.cpp \
    modelbase.cpp \
#    settings.cpp \
#    settingsdao.cpp \
#    settingsmodel.cpp \
    ticketsracemodel.cpp \
    ticketstrackmodel.cpp \
    dbtablebase.cpp \
    dbrecordbase.cpp \
    races.cpp \
    vehicles.cpp \
    tickets.cpp \
    observations.cpp \
    predictions.cpp \
    refpts.cpp \
    tracks.cpp

HEADERS += \
    databasemanager.h \
    narob-core_global.h \
    modelbase.h \
#    settings.h \
#    settingsdao.h \
#    settingsmodel.h \
    ticketsracemodel.h \
    ticketstrackmodel.h \
    dbtablebase.h \
    dbrecordbase.h \
    races.h \
    vehicles.h \
    tickets.h \
    observations.h \
    predictions.h \
    refpts.h \
    tracks.h
