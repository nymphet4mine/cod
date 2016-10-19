QT += core serialport
QT -= gui

TARGET = cod
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mcserialcom.cpp

HEADERS += \
    mcserialcom.h

