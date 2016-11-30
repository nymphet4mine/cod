#include "servo.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>
#include <pigpio.h>

servo::servo()
{
    gpioSetMode(PIN_PWM_Servo, PI_OUTPUT);
    gpioSetPWMfrequency(PIN_PWM_Servo, 50);
    gpioSetPWMrange(PIN_PWM_Servo, 4000);
}

void servo::setPWMSignal(int value)
{
    gpioPWM(PIN_PWM_Servo, value);
}
