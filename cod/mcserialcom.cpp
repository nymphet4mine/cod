#include "mcserialcom.h"


MCSerialCom::MCSerialCom() : QObject()
{
    serial = new QSerialPort(this);
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

        serial->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        //opens connection and sets a flag for the signal to set MainWindow labels if success
        if(serial->open(QIODevice::ReadWrite))
        {
            serialOpen = true;
        }
        else
            serialOpen = false;
    }
}

void MCSerialCom::closeSerial()
{
    if(!serialOpen) {qDebug() << "serial not open!"; return;}

    serial->close();
    serialOpen=false;
}

void MCSerialCom::startRead()
{
    if(!serialOpen) {qDebug() << "serial not open!"; return;}

    serial->clear(QSerialPort::AllDirections);
    QObject::connect(serial, &QSerialPort::readyRead, this, &MCSerialCom::readData);
    QByteArray send;

    send[0] = 0;
    send[1] = 1;
    send[2] = 2;
    send[3] = 4;
    send[4] = 8;

    serial->write(send);
}

void MCSerialCom::stopRead()
{
    if(!serialOpen) {qDebug() << "serial not open!"; return;}

    holds.clear();
    QByteArray send;
    for(int i = 0; i<5; i++)     send[i]=0;

    serial->write(send);

    QObject::disconnect(serial, &QSerialPort::readyRead, this, &MCSerialCom::readData);
}

int* MCSerialCom::get_received()
{
    return convData;
}

void MCSerialCom::readData()
{
    if(serial->bytesAvailable()== BYTEPACKSIZE)
    {
        qDebug() << QString::number(serial->bytesAvailable()) + " Bytes";
        QByteArray rec = serial->readAll();
        holds.append(rec);
        if(holds.count() < BYTESTORECEIVE) return;
        if(holds.count() > BYTESTORECEIVE) {holds.clear(); serial->clear(QSerialPort::Input); qDebug()<< "holds verworfen"; return;}
        ///////////////////////////////////////
        qDebug() << "RECS";
        for(int i = 0; i<holds.length(); i++)
            qDebug() << QString::number(holds[i]);
        qDebug() << "EOT";
        qDebug() << QString::number(holds.length()) + "Bytes hold";
        ///////////////////////////////////////
        convertReceive();
        holds.clear();
    }
    else
        serial->clear(QSerialPort::Input);
}

void MCSerialCom::convertReceive()
{
    int conv[BYTESTORECEIVE/4];
    for(unsigned int i=0; i<sizeof(conv)/4; i++)
        conv[i] = 0;


    for (unsigned int i=0; i<sizeof(conv)/4; i++){
        for(int j=0; j<4; j++)
        {
            conv[i]<<=8;
            conv[i]+=holds[4*i+j];
        }
        qDebug()<<QString::number(conv[i]);
    }
    convData = conv;
    emit mcRecReady();
}
