#include <QCoreApplication>
#include "engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    engine *e = new engine();

    return a.exec();
}

