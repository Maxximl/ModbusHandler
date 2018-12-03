#include "serialport.h"
#include <QSerialPort>
serialPort::serialPort(QObject *parent) : QObject(parent)
{
 sport = new QSerialPort;
 connect(sport, &QSerialPort::readyRead, this, [=]{emit dataReady();});
}

void serialPort::sendData(QByteArray data)
{
    sport->write(data);
}
