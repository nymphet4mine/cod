#include "servo.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>

servo::servo()
{
    pinMode(PIN_PWM_Servo, PWM_OUTPUT);
    softPwmCreate(PIN_PWM_Servo, 0, 100);
}

void servo::setPWMSignal(int value)
{
//    if(value > 14)
//        value = 14; // 14 == ganz links.
//    else if(value < 10)
//        value = 10; // 10 == ganz rechts.
    softPwmWrite(PIN_PWM_Servo, value);
    std::cout << "set";
    std::cout << value;
}
