#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonConnect_clicked();

    void on_pushButtonDisconnect_clicked();

    void readFromPort();

    void on_pushButtonLedOn_clicked();

    void on_pushButtonLedOff_clicked();

    void on_horizontalSliderIntensity_valueChanged(int value);

    void on_lineEditExpected_editingFinished();

    void on_horizontalSliderIntensity_sliderReleased();

private:
    void sendMessageToDevice(QString message);
    QSerialPort *device;
    void addToLogs(QString message);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
