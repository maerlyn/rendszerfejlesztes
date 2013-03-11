#ifndef RFSZERVER_H
#define RFSZERVER_H

#include <QObject>
#include <QTcpServer>

class RFSzerver : public QObject
{
  Q_OBJECT

  QTcpServer socket;

public:
  RFSzerver(QObject *parent = 0);

signals:

public slots:
  void incomingConnection();
  void readyRead();


};

#endif // RFSZERVER_H
