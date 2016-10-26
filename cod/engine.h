#ifndef ENGINE_H
#define ENGINE_H

#ifndef PIN_PWM
#define PIN_PWM 5
#endif

#ifndef PIN_DIR
#define PIN_DIR 7
#endif

#ifndef PIN_OUT_A
#define PIM_OUT_A 8
#endif

#ifndef PIN_OUT_B
#define PIN_OUT_B 9
#endif

#include <QObject>
#include <wiringPi.h>
#include <softPwm.h>

class engine
{
public:
    engine();
private:
};

#endif // ENGINE_H
