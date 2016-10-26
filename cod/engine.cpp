#include "engine.h"
#include <QDebug>

engine::engine()
{
    if(wiringPiSetup()<0) //init wiringpi
        qDebug()<<"Unable to setup wiringPi";
    if(softPwmCreate(PIN_PWM, 0, 100))
        qDebug()<<"Error creating PWM Pin";

    while(1) softPwmWrite(PIN_PWM, 40);
}
