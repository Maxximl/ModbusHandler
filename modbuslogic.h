#ifndef MODBUSLOGIC_H
#define MODBUSLOGIC_H

#include <QObject>

class ModbusLogic : public QObject
{
    Q_OBJECT
public:
    explicit ModbusLogic(QObject *parent = nullptr);
    QByteArray createRequest(uint8_t slaveID, 
                             uint8_t funcCode, 
                             uint16_t regAddress,
                             uint16_t regQuantity);
signals:

public slots:
private:
    uint16_t crc_chk( unsigned char* data, unsigned char length );
    
};

#endif // MODBUSLOGIC_H
