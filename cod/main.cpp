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
#include <signal.h>
#include "mythread.h"

using namespace std;
#include <QtCore/QCoreApplication>
#include "server.h"


int main()
{
    //MyThread mThread;
    //mThread.start();
    //mThread.wait();

    if(gpioInitialise() < 0)
    {
        cout << "pigpio inistialisation failed!\n";
        return 1;
    }

    Server myserver;
    //InputHandler *inputHandler = new InputHandler();
    //inputHandler->execute();

    gpioTerminate();
    cout << "gpio terminated!" << endl;
    return 0;
}

