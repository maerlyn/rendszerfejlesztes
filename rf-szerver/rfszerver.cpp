#include "rfszerver.h"

#include <iostream>
#include <string>
#include <QTcpSocket>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <map>

#include "../protobuf/rendszerfejlesztes.pb.h"

QString escape(const QString input);

RFSzerver::RFSzerver(QObject *parent) : QObject(parent), socket(this)
{
  qDebug() << socket.listen(QHostAddress::Any, 7462);
  if (!socket.isListening()) {
    exit(1);
  }

  QObject::connect(&socket, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
}

void RFSzerver::incomingConnection()
{
  QTcpSocket* client = socket.nextPendingConnection();
  QObject::connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
  QObject::connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));

  qDebug() << "client connected";
}

void RFSzerver::readyRead()
{
  QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());

  unsigned int message_length;
  QByteArray buffer;
  qDebug() << "readyRead";

  sock->read((char*)&message_length, 4);
  qDebug() << message_length;

  buffer = sock->read(message_length);
  protocol::AuthRequest arq;
  std::string s = QString(buffer).toStdString();
  arq.ParseFromString(s);
  std::cout << arq.username() << " / " << arq.password() << std::endl;

  protocol::AuthResponse arp;
  /*QSqlQuery query(QString("SELECT * FROM felhasznalo WHERE username=%1 AND `password`=%2;")
                  .arg(escape(QString(arq.username().c_str())))
                  .arg(escape(QString(arq.password().c_str()))));
  qDebug() << query.size();*/

  arp.set_status((arq.username() == "admin" && arq.password() == "admin") ? "ok" : "fail");

  std::cout << "sending resp. status: " << arp.status() << "... ";

  arp.SerializeToString(&s);
  message_length = s.length();
  sock->write((char*) &message_length, 4);
  sock->write(s.c_str());
  sock->flush();

  protocol::MegalloLista ml;
  std::map<int, std::string> megallok;
  megallok[1] = "elso megallo";
  megallok[2] = "masodik megallo";
  megallok[3] = "harmadik megallo";

  for (std::map<int, std::string>::iterator i = megallok.begin(); i != megallok.end(); ++i) {
      protocol::Megallo *m = ml.add_megallok();

      m->set_nev(i->second);
  }

  ml.SerializeToString(&s);
  message_length = s.length();
  sock->write((char*) &message_length, 4);
  sock->write(s.c_str());
  sock->flush();

  std::cout << "sent " << message_length << " bytes" << std::endl;

  sock->disconnect();
}
