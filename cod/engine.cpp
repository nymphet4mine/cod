#include "engine.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>

engine::engine()
{
    std::cout << "t2";
    if(wiringPiSetup()<0) //init wiringpi
        std::cout << "fehler";
    //leere if Anweisung
    pinMode(PIN_PWM, PWM_OUTPUT);
    pinMode(PIN_DIR, OUTPUT);
    if(softPwmCreate(PIN_PWM, 0, 100));

    //leere if Anweisung
}

void engine::setPWMSignal(int value)
{
    softPwmWrite(PIN_PWM, value);
}

void engine::setDir(bool high)
{
    if(high)
        digitalWrite(PIN_DIR, HIGH);
    else
        digitalWrite(PIN_DIR, LOW);
}
