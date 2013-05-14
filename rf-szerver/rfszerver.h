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

  void handleMegalloListaRequest(QTcpSocket *socket);
  void handleMegalloUjRequest(QTcpSocket *socket);
  void handleMegalloTorlesRequest(QTcpSocket *socket);

  void handleUtvonalUjRequest(QTcpSocket *socket);
  void handleUtvonalTorlesRequest(QTcpSocket *socket);
  void handleUtvonalRequest(QTcpSocket *socket);

  void handleBuszUjRequest(QTcpSocket *socket);
  void handleBuszTorlesRequest(QTcpSocket *socket);

  void handleSoforUjRequest(QTcpSocket *socket);
  void handleSoforTorlesRequest(QTcpSocket *socket);

  void handleJaratListaRequest(QTcpSocket *socket);
  void handleJaratUjRequest(QTcpSocket *socket);
  void handleJaratTorlesRequest(QTcpSocket *socket);

  void handleBeosztasUjRequest(QTcpSocket *socket);
  void handleBeosztasNapilistaRequest(QTcpSocket *socket);

  void handleShutdownRequest();
};

#endif // RFSZERVER_H
