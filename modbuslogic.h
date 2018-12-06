#ifndef MODBUSLOGIC_H
#define MODBUSLOGIC_H

#include <QObject>

class modbusLogic : public QObject
{
    Q_OBJECT
public:
    explicit modbusLogic(QObject *parent = nullptr);
    //QByteArray createRequest(uint8_t slaveID, );
signals:

public slots:
};

#endif // MODBUSLOGIC_H
