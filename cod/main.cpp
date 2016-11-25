#include <QCoreApplication>
#include "engine.h"
#include "servo.h"
#include <QTest>
#include <iostream>
#include <pigpio.h>
#include <termios.h>
#include <stdio.h>
#include "server.h"
#include "inputhandler.h"

using namespace std;
#include <QtCore/QCoreApplication>
#include "server.h"

int main()
{

    if(gpioInitialise() < 0)
    {
        cout << "pigpio inistialisation failed!\n";
        return 1;
    }

    Server myserver;
    InputHandler *inputHandler = new InputHandler();
    inputHandler->execute();

    gpioTerminate();
    return 0;
}

