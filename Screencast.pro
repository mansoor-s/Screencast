#-------------------------------------------------
#
# Project created by QtCreator 2012-07-25T03:04:51
#
#-------------------------------------------------

QT       += core gui

CONFIG += qxt
QXT = core gui

TARGET = Screencast
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Recorder.cpp \
    Countdown.cpp

HEADERS  += MainWindow.h \
    Recorder.h \
    Countdown.h \
    RecordInfo.h

FORMS    += MainWindow.ui \
    cowntdown.ui

RESOURCES += \
    icons.qrc


libs += l/usr/include/QxtCore
