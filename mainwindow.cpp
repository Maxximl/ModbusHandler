#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial/settingdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QSpinBox>
#include <modbuslogic.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(new settingDialog),
    serialPort(new QSerialPort),
    mbLogic(new ModbusLogic)
{
    ui->setupUi(this);

    initActionConnects();

    initInterface();
    initCreateRequestConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectToPort()
{
    if(!serialPort->open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, "Error!", serialPort->errorString());
    }
    else
    {
        ui->statusBar->showMessage("Connected to " + serialPort->portName());
    }
}

void MainWindow::disconnectFromPort()
{
    serialPort->close();
}

void MainWindow::initInterface()
{
     initFunctionComboBox();
     ui->createRequestRadio->setChecked(true);
     ui->slaveID->setEnabled(true);
     ui->functionCode->setEnabled(true);
     ui->regAddress->setEnabled(true);
     ui->regQuantity->setEnabled(true);

     ui->typeRequestRadio->setChecked(false);
     ui->typeRequestLineEdit->setEnabled(false);
}

void MainWindow::sendData()
{
    if(ui->createRequestRadio->isChecked())
    {
        QByteArray request;
        request = createRequest();
        serialPort->write(request);
        qDebug() << request;
    }

}

void MainWindow::putData()
{
   QByteArray newData;
   newData = serialPort->readAll();
   ui->plainTextEdit->insertPlainText(QString(newData) + '\n');

}

void MainWindow::chooseSendType()
{
    if(ui->typeRequestRadio->isChecked())
    {
        ui->typeRequestLineEdit->setEnabled(true);
    }
}

void MainWindow::initActionConnects()
{
    connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::showSettings);
    connect(ui->actionClose, &QAction::triggered, qApp, &QApplication::quit);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::connectToPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::disconnectFromPort);

    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendData);
    connect(ui->typeRequestRadio, &QRadioButton::clicked, this, &MainWindow::chooseSendType);
    connect(settings, &settingDialog::applyed, this, &MainWindow::applySettings);
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::putData);
}

void MainWindow::showSettings()
{
    settings->updateAvailablePorts();
    settings->show();
}

void MainWindow::applySettings()
{
    settingDialog::Settings currentSettings;
    currentSettings = settings->getSettings();

    serialPort->setPortName(currentSettings.name);
    serialPort->setBaudRate(currentSettings.baudRate);
    serialPort->setParity(currentSettings.parity);
    serialPort->setFlowControl(currentSettings.flowControl);
    serialPort->setStopBits(currentSettings.stopBits);
    serialPort->setDataBits(currentSettings.dataBits);
}

QByteArray MainWindow::createRequest()
{
    QByteArray createdRequestData;


   createdRequestData = mbLogic->createRequest(static_cast<uint8_t>(ui->slaveID->text().toInt()),
                           static_cast<uint8_t>(ui->functionCode->currentData().toInt()),
                           static_cast<uint16_t>(ui->regAddress->text().toInt()),
                           static_cast<uint16_t>(ui->regQuantity->text().toInt()));
    return createdRequestData;
}

void MainWindow::initFunctionComboBox()
{
    ui->functionCode->addItem("01(0x01)", 0x01);
    ui->functionCode->addItem("02(0x02)", 0x02);
    ui->functionCode->addItem("03(0x03)", 0x03);
    ui->functionCode->addItem("04(0x04)", 0x04);
    ui->functionCode->addItem("05(0x05)", 0x05);
    ui->functionCode->addItem("06(0x06)", 0x06);
    ui->functionCode->addItem("15(0x0F)", 0x0F);
    ui->functionCode->addItem("16(0x10)", 0x10);

}

void MainWindow::initCreateRequestConnects()
{
    connect(ui->slaveID, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateCRC);
    connect(ui->functionCode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::updateCRC);
    connect(ui->regAddress, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateCRC);
    connect(ui->regQuantity, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::updateCRC);
}

void MainWindow::updateCRC()
{
    QByteArray newRequest;
    uint16_t calculatedCRC = 0;
    newRequest = createRequest();
    calculatedCRC = (static_cast<uint8_t>(newRequest.at(6)) << 8) | (static_cast<uint8_t>(newRequest.at(7)));
    qDebug() << calculatedCRC;

    ui->CRC->setText(QString::number(calculatedCRC, 16));
}

