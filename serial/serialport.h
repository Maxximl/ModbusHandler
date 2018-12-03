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

signals:
void dataReady();

public slots:

private:
QSerialPort *sport = nullptr;
    
};

#endif // SERIALPORT_H
