#ifndef ROV_H
#define ROV_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>
#include <QTcpServer>
#include "qextserialport.h"

class ROV : public QObject
{
  Q_OBJECT
public:
  explicit ROV(QObject *parent = 0);

signals:

public slots:
  void setMotor(int index, bool forward, char speed); //*< Index from 0 to 8, Speed from 0 to 100


public slots:
  void sendDataToDriver();
  void readRequest();
  void newConnection();
private:
  char *motorValues;
  QTimer *refreshTimer;
  QTcpServer *tcpServer;
  QTcpSocket *tcpSocket;
  QextSerialPort *myExtSerialPort;
};

#endif // ROV_H
