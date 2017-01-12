#ifndef SERVO_H
#define SERVO_H

#ifndef PIN_PWM_Servo
#define PIN_PWM_Servo 18
#endif

#include <QObject>
#include <wiringPi.h>
#include <softPwm.h>


class servo
{
public:
    servo();
    void setPWMSignal(int value);
};

#endif // SERVO_H
