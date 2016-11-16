#include <QCoreApplication>
#include "engine.h"
#include "servo.h"
#include <QTest>
#include <iostream>
#include <pigpio.h>
#include <termios.h>
#include <stdio.h>

using namespace std;

int main()
{

    if(gpioInitialise() < 0)
    {
        cout << "pigpio inistialisation failed!\n";
        return 1;
    }

    servo *s = new servo();
    unsigned value;
    value = 62;
    int c;
    int count = 0;
    engine *e = new engine();
    bool dir = true;
    e->setDir(dir);
    system("/bin/stty raw");
    while((c=getchar())!= '.'){
        //putchar(c);
        if(c == '1' && count > 0)
            count = count - 10;
        else if ( c == '2')
            count = count + 10;
        else if(c == '7'){
            if(dir == true)
                dir = false;
            else
                dir = true;
            e->setDir(dir);
        }
        else if(c == '5' && value > 52)
        {
            value--;
            s->setPWMSignal(value);
        }
        else if(c == '4' && value < 75)
            value++;
            s->setPWMSignal(value);
        cout << count << endl;
        e->setPWMSignal(count);
    }
    system("/bin/stty cooked");

//    servo *s = new servo();
//    unsigned value;
//    value = 62;
//
//    for(;;)
//    {
//        char a = cin.get();
//        if(a == '4' && value > 51)
//            value--;
//        else if(a == '6' && value < 75)
//            value++;
//        s->setPWMSignal(value);
//    }


//    engine *e = new engine();
//    e->setDir(true);
//    for(;;){
//        int value;
//        cin >> value;
//        if(value == 0)
//            break;
//        e->setPWMSignal(value);
//    }

//    bool high = true;
//    for(;;){
//        cout << "enter value: ";
//        int i;
//        cin >> i;
//
//        if(i == 101)
//        {
//            high != high;
//            e->setDir(high);
//            continue;}
//        if(i == 102) break;
//        e->setPWMSignal(i);
//    }

//    for(int i = 0; i<101; i++)
//    {
//        e->setPWMSignal(i);
//        std::cout << i;
//        QTest::qSleep(100);
//    }
    gpioTerminate();
    return 0;
}

