#include "engine.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>
#include <pigpio.h>

bool currentDirection;
int currentPWMSignal;


engine::engine()
{
    gpioSetMode(PIN_PWM_Engine, PI_OUTPUT);
    gpioSetPWMfrequency(PIN_PWM_Engine, 40000);
    gpioSetPWMrange(PIN_PWM_Engine, 1000);
    gpioSetMode(PIN_DIR, PI_OUTPUT);
    setDir(true);
    setPWMSignal(0);
}

void engine::setPWMSignal(int value)
{
    if(value > 500)
    {
        printf("\nERROR (data > 100)\n");
        return;
    }

    if(currentPWMSignal == value)
        return;

    currentPWMSignal = value;
    writeEngineState();
    gpioPWM(PIN_PWM_Engine, value);
}

void engine::setDir(bool high)
{
    if(currentDirection == high)
        return;

    currentDirection = high;

    if(high)
        gpioWrite(PIN_DIR, PI_LOW);
    else
        gpioWrite(PIN_DIR, PI_HIGH);
}

void engine::writeEngineState()
{
    if(currentDirection == true)
        printf("Rückwärts: %d\n", currentPWMSignal);
    else
        printf("Vorwärts: %d\n", currentPWMSignal);

}
