#include "servo.h"
#include <QDebug>
#include <pthread.h>
#include <iostream>
#include <pigpio.h>

int currentPWMSignalServo;

servo::servo()
{
    gpioSetMode(PIN_PWM_Servo, PI_OUTPUT);
    gpioSetPWMfrequency(PIN_PWM_Servo, 50);
    gpioSetPWMrange(PIN_PWM_Servo, 4000);
}

void servo::setPWMSignal(int value)
{
    if(value < 195 || value > 295)
        return;
    gpioPWM(PIN_PWM_Servo, value);
    currentPWMSignalServo = value - 195;
    writeServoState();
}

void servo::writeServoState()
{
    if(currentPWMSignalServo < 50)
        printf("Rechts: %d\n", currentPWMSignalServo);
    else if(currentPWMSignalServo > 50)
        printf("Links: %d\n", currentPWMSignalServo);
    else if(currentPWMSignalServo == 50)
        printf("Mittig: %d\n", currentPWMSignalServo);


}
