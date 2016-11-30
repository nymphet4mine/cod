#include "servo.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>
#include <pigpio.h>

servo::servo()
{
    gpioSetMode(PIN_PWM_Servo, PI_OUTPUT);
    gpioSetPWMfrequency(PIN_PWM_Servo, 50);
    // range = 1023 (51 ganz rechts, 75 ganz links)
    gpioSetPWMrange(PIN_PWM_Servo, 4000);
}

void servo::setPWMSignal(int value)
{
    value = value + 195;
    //if(value > 75)
    //    value = 75;
    //else if(value < 51)
    //    value = 51;

    gpioPWM(PIN_PWM_Servo, value);
}
