#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#ifndef PIN_Sensor_Right
#define PIN_Sensor_Right 27
#endif

#ifndef PIN_Sensor_Left
#define PIN_Sensor_Left 22
#endif

#ifndef PIN_Sensor_Right_Red
#define PIN_Sensor_Right_Red 5
#endif

#ifndef PIN_Sensor_Right_Blue
#define PIN_Sensor_Right_Blue 6
#endif

#include <QtCore>

class InputHandler : public QThread
{
public:
    InputHandler();
    void app(int data);
    void microcontroller();
    void run();
    void stop();

    //void static alert(int pin, int level, unsigned int tick);
};

#endif // INPUTHANDLER_H
