#ifndef MCSERIALCOM_H
#define MCSERIALCOM_H
#include <QSerialPort>
#include <QSerialPortInfo>
#include "wiringPi.h"
#include <QDebug>
#include <QObject>
#include <QCoreApplication>
#include <pigpio.h>

#ifndef BYTESTORECEIVE
#define BYTESTORECEIVE 56
#endif

#ifndef BYTEPACKSIZE
#define BYTEPACKSIZE 4
#endif


class MCSerialCom : public QObject
{
    Q_OBJECT

public:
    MCSerialCom();
    ~MCSerialCom();
    QSerialPort *serial;
    void readData();
    void openSerial();
    void closeSerial();
    void startRead();
    void stopRead();
    int* get_received();
    bool serialOpen = false;
private:
    QByteArray holds;
    int *convData;
    void convertReceive();

signals:
    void mcRecReady();
};

#endif // MCSERIALCOM_H
