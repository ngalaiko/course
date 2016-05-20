#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T14:14:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_list
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    common.cpp \
    commondouble.cpp \
    display.cpp \
    queue.cpp \
    queuedouble.cpp \
    stack.cpp \
    stackdouble.cpp \
    displaytext.cpp \
    authors.cpp \
    queueCycle.cpp

HEADERS  += mainwindow.h \
    common.h \
    commonall.h \
    commondouble.h \
    display.h \
    queue.h \
    queuedouble.h \
    stack.h \
    stackdouble.h \
    displaytext.h \
    authors.h \
    queueCycle.h

FORMS    += mainwindow.ui \
    display.ui \
    displaytext.ui \
    authors.ui

RESOURCES += \
    code.qrc

DISTFILES += \
    code/deleteCycle.txt
