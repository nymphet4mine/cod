#include <QCoreApplication>
#include "engine.h"
#include "servo.h"
#include <QTest>
#include <iostream>

using namespace std;

int main()
{
    if(wiringPiSetup() < 0)
    {
        std::cout << "fehler";
        return 1;
    }

    servo *s = new servo();
    int value;
    std::cout << "enter value:";
    for(;;)
    {
        cin >> value;
        if(value == 101)
            return 0;
        s->setPWMSignal(value);
    }

//
//    engine *e = new engine();
//    cout << "t3";
//    bool high = true;
//    for(;;){
//        int i;
//        cin >> i;
//
//        if(i == 101){ high != high;  continue;}
//        if(i == 102) break;
//
//        e->setDir(high);
//        e->setPWMSignal(i);
//    }

//    for(int i = 0; i<101; i++)
//    {
//        e->setPWMSignal(i);
//        std::cout << i;
//        QTest::qSleep(100);
//    }
    return 0;
}

