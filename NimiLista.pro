#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T09:50:19
#
#-------------------------------------------------

QT      += core gui
QT      += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NimiLista
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
    tablemodel.cpp \
    namelistwidget.cpp \
    adddialog.cpp \
    workstations.cpp \
    person.cpp \
    departmentdialog.cpp \
    ticketwidget.cpp \
    movablelabel.cpp \
    ticketprinter.cpp \
    tableprinter.cpp

HEADERS += \
        mainwindow.h \
    tablemodel.h \
    namelistwidget.h \
    adddialog.h \
    person.h \
    workstations.h \
    departmentdialog.h \
    ticketwidget.h \
    movablelabel.h \
    ticketprinter.h \
    tableprinter.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    LICENSE.txt \
    testi.qmodel
