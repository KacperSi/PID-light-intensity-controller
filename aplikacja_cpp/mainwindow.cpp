#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete device;
}


void MainWindow::on_pushButtonSearch_clicked() {
    ui->comboBoxDevices->clear();
  this->addToLogs("Szukam urządzeń...");
  QList<QSerialPortInfo> devices;
  devices = QSerialPortInfo::availablePorts();

  for(int i = 0; i < devices.count(); i++) {
    this->addToLogs("Znalazłem urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
    ui->comboBoxDevices->addItem(devices.at(i).portName() + "\t" + devices.at(i).description());
  }
}

void MainWindow::sendMessageToDevice(QString message) {
  if(this->device->isOpen() && this->device->isWritable()) {
    if(message.length()<4)
    {
        for(int i=message.length();i<4;i++)
        {
            message="0"+message;
        }
    }
    this->addToLogs("Wysyłam informacje do urządzenia " + message);
    this->device->write(message.toStdString().c_str());
  } else {
    this->addToLogs("Nie mogę wysłać wiadomości. Port nie jest otwarty!");
  }
}

void MainWindow::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->Terminal->append(currentDateTime + "\t" + message);
}
//Dodaj interface zmiany parametrów połączenia!!!!!!!!
void MainWindow::on_pushButtonConnect_clicked()
{

    if(ui->comboBoxDevices->count() == 0) {
      this->addToLogs("Nie wykryto żadnych urządzeń!");
      return;
    }

    QString portName = ui->comboBoxDevices->currentText().split("\t").first();
    this->device->setPortName(portName);

    // OTWÓRZ I SKONFIGURUJ PORT:
    if(!device->isOpen()) {
    if(device->open(QSerialPort::ReadWrite)) {
      this->device->setBaudRate(QSerialPort::Baud9600);
      this->device->setDataBits(QSerialPort::Data8);
      this->device->setParity(QSerialPort::NoParity);
      this->device->setStopBits(QSerialPort::OneStop);
      this->device->setFlowControl(QSerialPort::NoFlowControl);

      this->addToLogs("Otwarto port szeregowy.");
      connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
      this->device->clear(QSerialPort::AllDirections);
    } else {
      this->addToLogs("Otwarcie porty szeregowego się nie powiodło!");
    }
    } else {
      this->addToLogs("Port już jest otwarty!");
      return;
    }
}

void MainWindow::on_pushButtonDisconnect_clicked()
{
    if(this->device->isOpen()) {
      this->device->close();
      this->addToLogs("Zamknięto połączenie.");
    } else {
      this->addToLogs("Port nie jest otwarty!");
      return;
    }
}

void MainWindow::readFromPort()
{
    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        //qDebug() << line;

        float sens_value=line.toFloat();
        ui->lcdNumberCurrent->display(sens_value);

        int expected_value =ui->horizontalSliderIntensity->value();
        ui->lcdNumberDeviation->display((1-sens_value/expected_value)*100);

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        line=line.left(pos)+" Lux";
        //qDebug() << line.left(pos);

        this->addToLogs(line);
      }
}

void MainWindow::on_pushButtonLedOn_clicked()
{

    this->sendMessageToDevice("1000");
    ui->horizontalSliderIntensity->setValue(1000);
}

void MainWindow::on_pushButtonLedOff_clicked()
{
    this->sendMessageToDevice("0000");
    ui->horizontalSliderIntensity->setValue(0000);
}

void MainWindow::on_horizontalSliderIntensity_valueChanged(int value)
{
    QString val=QString::number(value);
    ui->lineEditExpected->setText(val);
}

void MainWindow::on_lineEditExpected_editingFinished()
{
    int value=ui->lineEditExpected->text().toInt();
    ui->horizontalSliderIntensity->setValue(value);
    int send_value =ui->horizontalSliderIntensity->value();
    QString val=QString::number(send_value);
    this->sendMessageToDevice(val);

}

void MainWindow::on_horizontalSliderIntensity_sliderReleased()
{
    int value =ui->horizontalSliderIntensity->value();
    QString val=QString::number(value);
    this->sendMessageToDevice(val);
}
