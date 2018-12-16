#include "modbuslogic.h"
#include <QtDebug>
ModbusLogic::ModbusLogic(QObject *parent) : QObject(parent)
{

}

QByteArray ModbusLogic::createRequest(uint8_t slaveID,
                                      uint8_t funcCode, 
                                      uint16_t regAddress, 
                                      uint16_t regQuantity)
{
    uint8_t arrRequest[8];
    arrRequest[0] = slaveID;
    arrRequest[1] = funcCode;
    arrRequest[2] = regAddress >> 8;
    arrRequest[3] = regAddress & 0xFF;
    arrRequest[4] = regQuantity >> 8;
    arrRequest[5] = regQuantity & 0xFF;
    
    uint16_t CRC;
    CRC = crc_chk(arrRequest, 6);

    arrRequest[6] = CRC >> 8;
    arrRequest[7] = CRC & 0xFF;
    
    QByteArray request;
    request = QByteArray(reinterpret_cast<char*>(arrRequest), 8);
    return  request;
    
}

uint16_t ModbusLogic::crc_chk ( unsigned char* data, unsigned char length )
  {
     int j;
     uint16_t reg_crc = 0xFFFF;
    while (length--)
    {
      reg_crc ^= *data++;
      for(j=0;j<8;j++)
      {
         if(reg_crc & 0x01)
          {
            reg_crc = (reg_crc >> 1) ^ 0xA001;
          }
        else
          {
            reg_crc = reg_crc >> 1;
          }
      }
    }
    return reg_crc;
  }
