#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
class ModbusLogic;
class settingDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
    void putData();

private:
    Ui::MainWindow *ui;
    settingDialog *settings = nullptr;
    QSerialPort *serialPort = nullptr;
    ModbusLogic *mbLogic = nullptr;

    void initInterface();
    void initActionConnects();
    void initFunctionComboBox();
    QByteArray createRequest();

    void initCreateRequestConnects();

private slots:
    void sendData();
    void chooseSendType();
    void connectToPort();
    void disconnectFromPort();
    void updateCRC();

    void applySettings();
private slots:
    void showSettings();
protected:
    virtual void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
