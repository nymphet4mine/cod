#include "engine.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>
#include <pigpio.h>

engine::engine()
{
   // std::cout << "t2";
   // if(wiringPiSetup()<0) //init wiringpi
   //     std::cout << "fehler";
   // //leere if Anweisung
   // pinMode(PIN_PWM, PWM_OUTPUT);
   // pinMode(PIN_DIR, OUTPUT);
   // if(softPwmCreate(PIN_PWM, 0, 10));

    //leere if Anweisung

    gpioSetMode(PIN_PWM_Engine, PI_OUTPUT);
    gpioSetPWMfrequency(PIN_PWM_Engine, 40000);
    gpioSetMode(PIN_DIR, PI_OUTPUT);
}

void engine::setPWMSignal(int value)
{
    //softPwmWrite(PIN_PWM, value);
    //std::cout << value << endl;
    gpioPWM(PIN_PWM_Engine, value);
}

void engine::setDir(bool high)
{
    if(high)
    {
        gpioWrite(PIN_DIR, PI_LOW);
        std::cout << "Rückwärt";
    }
    else
    {
        gpioWrite(PIN_DIR, PI_HIGH);
        std::cout << "Vorwärts";
    }
}
