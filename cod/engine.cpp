#include "engine.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>
#include <pigpio.h>

engine::engine()
{
    gpioSetMode(PIN_PWM_Engine, PI_OUTPUT);
    gpioSetPWMfrequency(PIN_PWM_Engine, 40000);
    gpioSetMode(PIN_DIR, PI_OUTPUT);
    setDir(true);
}

void engine::setPWMSignal(int value)
{
    gpioPWM(PIN_PWM_Engine, value);
}

void engine::setDir(bool high)
{
    if(high)
        gpioWrite(PIN_DIR, PI_LOW);
    else
        gpioWrite(PIN_DIR, PI_HIGH);
}

void engine::writeDirection(bool dir){
    if(dir == true)
        std::cout << "Rückwärts";
    else
        std::cout << "Vorwärts";

}
