#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class Dialog;
}

class settingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit settingDialog(QDialog *parent = nullptr);
    struct Settings
    {
        QString name;
        QSerialPort::BaudRate baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    };

    Settings getSettings();
    void updateAvailablePorts();
signals:
void applyed();

private slots:
void apply();

private:
Ui::Dialog *ui;

QByteArray data;
Settings currentSettings;

void updateSettings();
void initSettings();


};

#endif // SERIALPORT_H
