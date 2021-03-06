QT += core serialport testlib
QT += core
QT += network widgets
QT -= gui

TARGET = cod
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    engine.cpp \
    servo.cpp \
    server.cpp \
    inputhandler.cpp \
    mythread.cpp

HEADERS += \
    engine.h \
    servo.h \
    server.h \
    inputhandler.h \
    mythread.h

target.path = qtTest
INSTALLS += target

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

INCLUDEPATH += $$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/include
DEPENDPATH += $$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/lib/release/ -lpigpio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/lib/debug/ -lpigpio
else:unix: LIBS += -L$$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/lib/ -lpigpio

INCLUDEPATH += $$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/include
DEPENDPATH += $$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/include

