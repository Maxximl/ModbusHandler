#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial/serialport.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), serialPt(new serialPort)
{
    ui->setupUi(this);
    connect(serialPt, &serialPort::dataReady, this, &MainWindow::putData);
    
    initInterface();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::putData()
{
    QByteArray newData;
    newData = serialPt->getData();
    /*
    здесь как-то отображаем полученные данные
    */

}

void MainWindow::initInterface()
{
 ui->createRequestRadio->setChecked(true);
 ui->typeRequestRadio->setChecked(false);

 ui->slaveID->setEnabled(false);
 ui->functionCode->setEnabled(false);
 ui->regAddress->setEnabled(false);
 ui->regQuantity->setEnabled(false);
}
