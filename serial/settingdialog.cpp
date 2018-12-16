#include "settingdialog.h"
#include "ui_serialportsettings.h"
#include <QDebug>
#include <QSerialPortInfo>

settingDialog::settingDialog(QDialog *parent) : QDialog(parent),
    ui(new Ui::Dialog)
{
 ui->setupUi(this);

 connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &settingDialog::apply);

 initSettings();
 updateSettings();
 setModal(true);
}

void settingDialog::initSettings()
{
    ui->baudRate->addItem(QString("9600"), QSerialPort::Baud9600);
    ui->baudRate->addItem(QString("19200"), QSerialPort::Baud19200);
    ui->baudRate->addItem(QString("38400"), QSerialPort::Baud38400);
    ui->baudRate->addItem(QString("57600"), QSerialPort::Baud57600);
    ui->baudRate->addItem(QString("115200"), QSerialPort::Baud115200);

    ui->parity->addItem(QString("No Parity"), QSerialPort::NoParity);
    ui->parity->addItem(QString("Even Parity"), QSerialPort::EvenParity);
    ui->parity->addItem(QString("Odd Parity"), QSerialPort::OddParity);

    ui->dataBits->addItem(QString("5 Bits"), QSerialPort::Data5);
    ui->dataBits->addItem(QString("6 Bits"), QSerialPort::Data6);
    ui->dataBits->addItem(QString("7 Bits"), QSerialPort::Data7);
    ui->dataBits->addItem(QString("8 Bits"), QSerialPort::Data8);
    ui->dataBits->setCurrentIndex(3);

    ui->flowControl->addItem(QString("No flow control"), QSerialPort::NoFlowControl);
    ui->flowControl->addItem(QString("Hardware control"), QSerialPort::HardwareControl);
    ui->flowControl->addItem(QString("Software control"), QSerialPort::SoftwareControl);

    ui->stopBits->addItem(QString("One stoop"), QSerialPort::OneStop);
    ui->stopBits->addItem(QString("Two stop"), QSerialPort::TwoStop);

//    const auto portInfo = QSerialPortInfo::availablePorts();
//    for (const QSerialPortInfo &info : portInfo)
//    {
//        ui->port->addItem(QString(info.portName()));
//    }
}

void settingDialog::updateSettings()
{
   currentSettings.name = ui->port->currentText();
   currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(ui->baudRate->currentData().toInt());
   currentSettings.parity = static_cast<QSerialPort::Parity>(ui->parity->currentData().toInt());
   currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(ui->flowControl->currentData().toInt());
   currentSettings.dataBits = static_cast<QSerialPort::DataBits>(ui->dataBits->currentData().toInt());
   currentSettings.stopBits = static_cast<QSerialPort::StopBits>(ui->stopBits->currentData().toInt());
}

void settingDialog::apply()
{
    updateSettings();
    emit applyed();
    hide();
}

void settingDialog::updateAvailablePorts()
{
    ui->port->clear();
    const auto portInfo = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : portInfo)
    {
        ui->port->addItem(QString(info.portName()));
    }
}

settingDialog::Settings settingDialog::getSettings()
{
    return currentSettings;
}
