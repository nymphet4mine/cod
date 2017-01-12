#include "inputhandler.h"
#include "servo.h"
#include "engine.h"
#include <stdio.h>
#include <termios.h>
#include <iostream>
#include <qthread.h>
#include <pigpio.h>
#include <qthread.h>
#include <time.h>
#include <QtCore>

using namespace std;

servo *s;
engine *e;
int servo_offset = 195;
bool running = false;


InputHandler::InputHandler()
{
    gpioSetMode(PIN_Sensor_Right, PI_INPUT);
    gpioSetMode(PIN_Sensor_Left, PI_INPUT);
    s = new servo();
    e = new engine();
}

void InputHandler::run()
{
    printf("running...\n");
    microcontroller();
}

void InputHandler::stop()
{
    running = false;
    printf("stopped!\n");
}

void InputHandler::app(int data)
{  

    if(data > 25700)
    {
        printf( "got %d\n", data );
    }
    unsigned servoData = data / 256;
    s->setPWMSignal(servoData + servo_offset);

    unsigned engineData = data - (servoData * 256);

    if(engineData >= 50)
    {
        e->setDir(false);
        //printf("data: %d\n", engineData);
        e->setPWMSignal((((engineData - 50) * 10) / 10) * 10);
    }
    else
    {
        e->setDir(true);
        e->setPWMSignal((((50 - engineData) * 10) / 10) * 10);
    }
}
//void InputHandler::alert(int pin, int level, unsigned int tick)
//{
//        printf("changed: pin: %d level: %d\n", pin, level);
//}

void InputHandler::microcontroller()
{
 //   gpioSetAlertFunc(LDR, alert);
 //   while (1)
 //      {
 //         gpioDelay(10000); /* nominal 100 readings per second */
 //      }
//    int level_right = 0;
//    int level_left = 0;
//    while(true)
//    {
//        level_left = gpioRead(PIN_Sensor_Left);
//        level_right = gpioRead(PIN_Sensor_Right);
//
//        if(level_left == level_right)
//                s->setPWMSignal(50 + servo_offset);
//        else if(level_left)
//            s->setPWMSignal(0 + servo_offset);
//        else if(level_right)
//            s->setPWMSignal(100 + servo_offset);
//
//        printf("Left: %d    Right: %d\n", level_left, level_right);
//    }
    printf("in microC");
    running = true;
    int level_right = 0;
    int level_left = 0;
    int previewState = 0;
    int currentState = 0;
    int count = 0;
    int servoValue = 0;
    int engineValue = 0;
    int drive = 100;
    int dontDrive = 0;
    e->setDir(false);
    while(true)
    {
        if(running == false)
            break;
        level_right = gpioRead(PIN_Sensor_Right);
        level_left = gpioRead(PIN_Sensor_Left);

        if(level_left <= 0 && level_right <= 0 && previewState != 1)
        {
            servoValue = 50;
            engineValue = drive;
            currentState = 1;
        }
        else if(level_left > 0 && level_right <= 0 && previewState != 2)
        {
            servoValue = 0;
            engineValue = drive;
            currentState = 2;
        }
        else if(level_right > 0 && level_left <= 0 && previewState != 3)
        {
            servoValue = 100;
            engineValue = drive;
            currentState = 3;
        }
        else if(level_left > 0 && level_right > 0 && previewState != 4)
        {
            servoValue = 50;
            engineValue = dontDrive;
            currentState = 4;
        }

        if(currentState != previewState)
        {
            s->setPWMSignal(servoValue + servo_offset);
            e->setPWMSignal(engineValue);
            count++;
            printf("[%d]\tLeft: %d    Right: %d   PreState: %d -> CurState %d\n", count, level_left, level_right, previewState, currentState);
        }
        previewState = currentState;
    }

}


//    unsigned value = 62;
//    int c;
//    int count = 0;
//    bool dir = true;
//
//    system("/bin/stty raw");
//    while((c=getchar())!= '.'){
//        system("clear");
//        //putchar(c);
//        if(c == '1' && count > 0)
//            count = count - 10;
//        else if ( c == '2' && count < 100)
//            count = count + 10;
//        else if(c == '7'){
//            if(dir == true)
//                dir = false;
//            else
//                dir = true;
//            e->setDir(dir);
//        }
//        else if(c == '6' && value > 52)
//        {
//            value--;
//            value = 52;
//            s->setPWMSignal(value);
//        }
//        else if(c == '4' && value < 75)
//        {
//            value++;
//            value = 75;
//            s->setPWMSignal(value);
//        }
//        else if(c == '5')
//        {
//
//            value++;
//            value = 61;
//            s->setPWMSignal(value);
//        }
//        e->writeDirection(dir);
//        cout << "\n Power: ";
//        cout << count << endl;
//        cout << " \n";
//        e->setPWMSignal(count);
//    }
//    system("/bin/stty cooked");
