#ifndef RFSZERVER_H
#define RFSZERVER_H

#include <QObject>
#include <QTcpSocket>
#include <networkhelper.h>

class RFSzerver : public QObject
{
  Q_OBJECT
  networkhelper helper;

public:
  RFSzerver(QObject *parent = 0);

signals:

public slots:
  void incomingConnection();
  void readyRead();

  void handleAuthRequest(QTcpSocket *socket);
  void handleUtvonallistaRequest(QTcpSocket *socket);
  void handleBuszlistaRequest(QTcpSocket *socket);
  void handleSoforlistaRequest(QTcpSocket *socket);
  void handleUtvonalBuszSoforRequest(QTcpSocket *socket);


};

#endif // RFSZERVER_H
