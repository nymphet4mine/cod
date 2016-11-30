#include "mcserialcom.h"
#include <iostream>


MCSerialCom::MCSerialCom() : QObject()
{
    serial = new QSerialPort(this);
    connect(this, SIGNAL(mcRecReady()), this, SLOT(mcAusgabe()));
    openSerial();
}

MCSerialCom::~MCSerialCom()
{
    delete serial;
}

void MCSerialCom::openSerial()
{
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        serial->setPort(info);
        serial->setPortName(info.portName());

        serial->setBaudRate(QSerialPort::Baud19200, QSerialPort::AllDirections);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //opens connection and sets a flag for the signal to set MainWindow labels if success
        if(serial->open(QIODevice::ReadWrite))
        {
            serialOpen = true;
            std::cout << "serial open";
        }
        else
        {
            std::cout << "serial not open";
            serialOpen = false;
        }
    }
}

void MCSerialCom::closeSerial()
{
    if(!serialOpen) {std::cout << "serial not open!"; return;}

    serial->close();
    serialOpen=false;
}

void MCSerialCom::startRead()
{
    if(!serialOpen) {std::cout << "serial not open!"; return;}

    serial->clear(QSerialPort::AllDirections);
    QObject::connect(serial, &QSerialPort::readyRead, this, &MCSerialCom::readData);
    QByteArray send;

    send[0] = 196;

    serial->write(send);
}

void MCSerialCom::stopRead()
{
    if(!serialOpen) {std::cout << "serial not open!"; return;}

    QByteArray send;
    send[0]=0;

    serial->write(send);

    QObject::disconnect(serial, &QSerialPort::readyRead, this, &MCSerialCom::readData);
}

int* MCSerialCom::get_received()
{
    return convData;
}

void MCSerialCom::mcAusgabe()
{
    std::cout << "fertig";
    stopRead();
}

void MCSerialCom::readData()
{
    if(serial->bytesAvailable()== BYTEPACKSIZE)
    {
//        std::cout << QString::number(serial->bytesAvailable()) + " Bytes";
        QByteArray rec = serial->readAll();
        if(rec.count() < BYTESTORECEIVE) return;
        if(rec.count() > BYTESTORECEIVE) {rec.clear(); serial->clear(QSerialPort::Input); std::cout << "rec verworfen"; return;}
        ///////////////////////////////////////
//        std::cout << "REC";
//        for(int i = 0; i<rec.length(); i++)
//            std::cout << QString::number(rec[i]);
//        std::cout << "EOT";
//        std::cout << QString::number(rec.length()) + "Bytes hold";
        ///////////////////////////////////////
        convertReceive(rec);
    }
    else
        serial->clear(QSerialPort::Input);
}

void MCSerialCom::convertReceive(QByteArray rec)
{
    int conv[BYTESTORECEIVE];
    for(unsigned int i=0; i<sizeof(conv)/4; i++)
        conv[i] = rec[i];

    convData = conv;
    emit mcRecReady();
}
