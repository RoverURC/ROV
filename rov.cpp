#include "rov.h"

ROV::ROV(QObject *parent) :
  QObject(parent)
{
  motorValues = new char[8];
  for(int i=0;i<8;i++){
    motorValues[i] = 0;
  }

  refreshTimer = new QTimer(this);
  connect(refreshTimer,SIGNAL(timeout()),
          this,SLOT(sendDataToDriver()));
  refreshTimer->start(20);

  tcpServer = new QTcpServer(this);
  tcpServer->listen(QHostAddress::Any,3000);
  connect(tcpServer,SIGNAL(newConnection()),
          this,SLOT(newConnection()));
  tcpSocket = new QTcpSocket(this);

  myExtSerialPort= new QextSerialPort("/dev/ttyAMA0");
  myExtSerialPort->setBaudRate(BAUD115200);
  myExtSerialPort->setFlowControl(FLOW_OFF);
  myExtSerialPort->setParity(PAR_NONE);
  myExtSerialPort->setDataBits(DATA_8);
  myExtSerialPort->setStopBits(STOP_1);
  //port->setQueryMode(QextSerialPort::Polling);
  myExtSerialPort->close();

  if (myExtSerialPort->open(QIODevice::ReadWrite) == true){
    qDebug("Port is opened");
  }
  else{
    qDebug("Port is not opened");
  }
}

//Set motor value in internal array, sending over UART every refreshTimer timeout.
void ROV::setMotor(int index, bool forward, char speed)
{
  if(index<0 || index<8)
    return;
  if(speed<0 || speed > 100)
    return;
  if(forward == true);
    speed = speed | 0b10000000;  //Ustaw 1 na pierwszym miejscu
  else
    speed = speed & 0b01111111;
  motorValues[i] = speed;
}

void ROV::sendDataToDriver()
{
  QByteArray array;
  array.append(0xe5);
  for(int i=0;i<8;i++){
    array.append(motorValues[i]);
  }
  myExtSerialPort->write(array);
}

void ROV::readRequest(){
  qDebug()<<"Incoming request";

}

void ROV::newConnection(){
  tcpSocket = tcpServer->nextPendingConnection();
  connect(tcpSocket,SIGNAL(readyRead()),
          this,SLOT(readRequest()));
}
