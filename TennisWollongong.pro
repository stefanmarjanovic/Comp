#-------------------------------------------------
#
# Project created by QtCreator 2018-08-17T13:47:36
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TennisWollongong
TEMPLATE = app

VERSION = 0.1.321
DEFINES += VERSION_STRING=\\\"$${VERSION}\\\"

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
    refine.cpp \
    player.cpp \
    addplayerdiag.cpp \
    editplayerdiag.cpp \
    datepick.cpp \
    familysearchdiag.cpp \
    addvenuediag.cpp \
    venue.cpp \
    editvenuediag.cpp \
    addteamdialog.cpp \
    editteamdiag.cpp \
    teamsearchdiag.cpp \
    team.cpp \
    divisionselector.cpp \
    compselector.cpp \
    database.cpp \
    settings.cpp \
    addcompdiag.cpp \
    viewdraw.cpp \
    adddivisiondiag.cpp \
    division.cpp \
    venueselector.cpp \
    payment.cpp \
    addpaymentdiag.cpp \
    playerselector.cpp \
    editcompdiag.cpp

HEADERS += \
        mainwindow.h \
    refine.h \
    player.h \
    player.h \
    addplayerdiag.h \
    editplayerdiag.h \
    datepick.h \
    familysearchdiag.h \
    addvenuediag.h \
    venue.h \
    editvenuediag.h \
    addteamdialog.h \
    editteamdiag.h \
    teamsearchdiag.h \
    team.h \
    divisionselector.h \
    compselector.h \
    database.h \
    settings.h \
    addcompdiag.h \
    adddivisiondiag.h \
    division.h \
    viewdraw.h \
    venueselector.h \
    payment.h \
    addpaymentdiag.h \
    playerselector.h \
    editcompdiag.h

FORMS += \
        mainwindow.ui \
    addplayerdiag.ui \
    editplayerdiag.ui \
    datepick.ui \
    refine.ui \
    familysearchdiag.ui \
    addvenuediag.ui \
    editvenuediag.ui \
    addteamdialog.ui \
    editteamdiag.ui \
    teamsearchdiag.ui \
    divisionselector.ui \
    settings.ui \
    about.ui \
    addcompdiag.ui \
    viewdraw.ui \
    adddivisiondiag.ui \
    compselector.ui \
    venueselector.ui \
    addpaymentdiag.ui \
    playerselector.ui \
    editcompdiag.ui

RESOURCES += \
    resources.qrc


