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
#define BYTESTORECEIVE 6
#endif

#ifndef BYTEPACKSIZE
#define BYTEPACKSIZE 1
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
    int *convData;
    void convertReceive(QByteArray rec);

private slots:
    void mcAusgabe();

signals:
    void mcRecReady();
};

#endif // MCSERIALCOM_H
