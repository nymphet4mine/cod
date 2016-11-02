#include <QCoreApplication>
#include "engine.h"
#include <QTest>
#include <iostream>

using namespace std;

int main()
{
    cout << "t1";

    engine *e = new engine();
    cout << "t3";
    bool high = true;
    for(;;){
        int i;
        cin >> i;

        if(i == 101){ high != high;  continue;}
        if(i == 102) break;

        e->setDir(high);
        e->setPWMSignal(i);
    }
//    for(int i = 0; i<101; i++)
//    {
//        e->setPWMSignal(i);
//        std::cout << i;
//        QTest::qSleep(100);
//    }
    return 0;
}

