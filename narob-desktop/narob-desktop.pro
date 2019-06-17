#-------------------------------------------------
#
# Project created by QtCreator 2018-01-17T17:25:03
#
#-------------------------------------------------

QT       += core gui widgets sql serialport charts

TARGET = narob-desktop
TEMPLATE = app

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
    main.cpp \
    mainwindow.cpp \
    dashboardtab.cpp \
    trace.cpp \
    weathergraphwidget.cpp \
    weathertab.cpp \
    settingstab.cpp \
    racecontroltab.cpp \
    ticketentrytab.cpp \
    trackhistorytab.cpp \
    logbooktab.cpp \
    predictiontab.cpp \
    delegates.cpp \
    tableeditwidgetbase.cpp \
    tablewidgetbase.cpp \
    trackswidget.cpp \
    trackdialog.cpp \
    racedialog.cpp \
    raceswidget.cpp \
    vehicleswidget.cpp \
    vehicledialog.cpp \
    ticketswidget.cpp \
    ticketdialog.cpp \
    observationswidget.cpp \
    providerbox.cpp \
    ticketseditwidget.cpp \
    tabledisplaywidgetbase.cpp \
    dialogbase.cpp \
    previouspredictionswidget.cpp \
    predictionswidget.cpp \
    ticketpredictionsdialog.cpp

HEADERS += \
    mainwindow.h \
    dashboardtab.h \
    trace.h \
    weathergraphwidget.h \
    weathertab.h \
    settingstab.h \
    racecontroltab.h \
    trackhistorytab.h \
    ticketentrytab.h \
    logbooktab.h \
    predictiontab.h \
    delegates.h \
    tableeditwidgetbase.h \
    tablewidgetbase.h \
    trackswidget.h \
    trackdialog.h \
    raceswidget.h \
    racedialog.h \
    vehicleswidget.h \
    vehicledialog.h \
    ticketswidget.h \
    ticketdialog.h \
    observationswidget.h \
    providerbox.h \
    ticketseditwidget.h \
    tabledisplaywidgetbase.h \
    dialogbase.h \
    previouspredictionswidget.h \
    predictionswidget.h \
    ticketpredictionsdialog.h

FORMS += \
    mainwindow.ui \
    dashboardtab.ui \
    weathergraphwidget.ui \
    weathertab.ui \
    settingstab.ui \
    tableeditwidgetbase.ui \
    tablewidgetbase.ui \
    trackdialog.ui \
    racedialog.ui \
    vehicledialog.ui \
    ticketdialog.ui \
    racecontroltab.ui \
    trackhistorytab.ui \
    ticketentrytab.ui \
    logbooktab.ui \
    predictiontab.ui \
    ticketpredictionsdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../narob-core/release/ -lnarob-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../narob-core/debug/ -lnarob-core
else:unix: LIBS += -L$$OUT_PWD/../narob-core/ -lnarob-core

INCLUDEPATH += $$PWD/../narob-core
DEPENDPATH += $$PWD/../narob-core
