#include "serialport.h"
#include <QSerialPort>
serialPort::serialPort(QObject *parent) : QObject(parent)
{
 sPort = new QSerialPort;
 connect(sPort, &QSerialPort::readyRead, this, &serialPort::readData);
}

void serialPort::sendData(QByteArray data)
{
    sPort->write(data);
}

QByteArray serialPort::getData()
{
    return data;
}

void serialPort::readData()
{
    data = sPort->readAll();
    emit dataReady();
}
