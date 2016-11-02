#ifndef ENGINE_H
#define ENGINE_H

#ifndef PIN_PWM
#define PIN_PWM 1
#endif

#ifndef PIN_DIR
#define PIN_DIR 0
#endif

#include <QObject>
#include <wiringPi.h>
#include <softPwm.h>

class engine
{
public:
    engine();
    void setPWMSignal(int value);
    void setDir(bool high);
private:
};

#endif // ENGINE_H
