#ifndef ENGINE_H
#define ENGINE_H

#ifndef PIN_PWM_Engine
#define PIN_PWM_Engine 24
#endif

#ifndef PIN_DIR
#define PIN_DIR 17
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
    void writeEngineState();
private:
};

#endif // ENGINE_H
