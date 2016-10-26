QT += core serialport
QT -= gui

TARGET = cod
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mcserialcom.cpp \
    engine.cpp

HEADERS += \
    mcserialcom.h \
    engine.h

target.path = qtTest
INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/lib/ -lwiringPi

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
