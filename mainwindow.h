#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class serialPort;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void putData();
private:
    Ui::MainWindow *ui;
    serialPort *serialPt = nullptr;

    void initInterface();
};

#endif // MAINWINDOW_H
