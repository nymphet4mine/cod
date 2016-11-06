QT += core serialport testlib
QT -= gui

TARGET = cod
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mcserialcom.cpp \
    engine.cpp \
    servo.cpp

HEADERS += \
    mcserialcom.h \
    engine.h \
    servo.h

target.path = qtWorkspace
INSTALLS += target

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/lib/ -lwiringPi

INCLUDEPATH += $$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/include
DEPENDPATH += $$PWD/../../../../../../../SysGCC/Raspberry/arm-linux-gnueabihf/sysroot/usr/include
