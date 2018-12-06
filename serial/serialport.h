#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
class QSerialPort;
class serialPort : public QObject
{
    Q_OBJECT
public:
    explicit serialPort(QObject *parent = nullptr);

void sendData(QByteArray data);

QByteArray  getData();

signals:
void dataReady();

private slots:
void readData();

private:
QSerialPort *sPort = nullptr;

QByteArray data;
    
};

#endif // SERIALPORT_H
