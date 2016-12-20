#include "inputhandler.h"
#include "servo.h"
#include "engine.h"
#include <stdio.h>
#include <termios.h>
#include <iostream>

using namespace std;

servo *s;
engine *e;

InputHandler::InputHandler()
{
    s = new servo();
    e = new engine();
}

void InputHandler::app(int data)
{  
    unsigned servoData = data / 65536;
    s->setPWMSignal(servoData + 195);

    unsigned engineData = data - (servoData * 65536);

    if(engineData >= 50)
    {
        e->setDir(false);
        printf("data: %d\n", engineData);
        e->setPWMSignal((((engineData - 50) * 10) / 10) * 10);
    }
    else
    {
        e->setDir(true);
        e->setPWMSignal((((50 - engineData) * 10) / 10) * 10);
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
