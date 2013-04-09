#include "rfszerver.h"

#include <iostream>
#include <string>
#include <QTcpSocket>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <map>

#include "../protobuf/rendszerfejlesztes.pb.h"
#include "utvonaldb.h"
#include "megallodb.h"

RFSzerver::RFSzerver(QObject *parent) : QObject(parent)
{
  QObject::connect(&(helper.socket), SIGNAL(newConnection()), this, SLOT(incomingConnection()));

  UtvonalDB::load();
  MegalloDB::load();
}

void RFSzerver::incomingConnection()
{
  QTcpSocket* client = helper.socket.nextPendingConnection();
  QObject::connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
  QObject::connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));

  qDebug() << "client connected";
}

void RFSzerver::readyRead()
{
  qDebug() << "readyRead";
  QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());
  protocol::MessageType_Types mt = helper.readMessageType(sock);
  qDebug() << "got a type";

  switch (mt) {
    case protocol::MessageType_Types_AUTH_TYPE:
      handleAuthRequest(sock);
      break;

    case protocol::MessageType_Types_UTVONALLISTA_REQUEST:
      handleUtvonallistaRequest(sock);
      break;

    case protocol::MessageType_Types_BUSZLISA_REQUEST:
      handleBuszlistaRequest(sock);
      break;

    case protocol::MessageType_Types_SOFORLISTA_REQUEST:
      handleSoforlistaRequest(sock);
      break;

    case protocol::MessageType_Types_UTVONAL_BUSZ_SOFOR_REQUEST:
      handleUtvonalBuszSoforRequest(sock);
      break;

    case protocol::MessageType::MEGALLO_LISTA_REQUEST:
      handleMegalloListaRequest(sock);
      break;

    case protocol::MessageType::MEGALLO_UJ_REQUEST:
      std::cout << "megallo_uj_req\n";
      handleMegalloUjRequest(sock);
      break;

    case protocol::MessageType::MEGALLO_TORLES_REQUEST:
      handleMegalloTorlesRequest(sock);
      break;

    case protocol::MessageType::UTVONAL_UJ_REQUEST:
      handleUtvonalUjRequest(sock);
      break;

    case protocol::MessageType::UTVONAL_TORLES_REQUEST:
      handleUtvonalTorlesRequest(sock);
      break;

    case protocol::MessageType::SHUTDOWN:
      handleShutdownRequest();
      break;
  }
}

void RFSzerver::handleAuthRequest(QTcpSocket *sock)
{
    protocol::AuthRequest arq;
    helper.readMessage(arq, sock);

    protocol::AuthResponse arp;
    arp.set_status((arq.username() == "admin" && arq.password() == "admin") ? "ok" : "fail");

    helper.sendMessage(arp, sock);
}

void RFSzerver::handleUtvonallistaRequest(QTcpSocket *sock)
{
    helper.sendMessage(UtvonalDB::findAll(), sock);
}

void RFSzerver::handleBuszlistaRequest(QTcpSocket *socket)
{
    std::map<int, std::string> buszok;
    buszok[1] = "AAA-111";

    protocol::BuszLista buszlista;

    for (std::map<int, std::string>::iterator i = buszok.begin(); i != buszok.end(); ++i) {
        protocol::Busz *b = buszlista.add_buszok();

        b->set_id(i->first);
        b->set_rendszam(i->second);
    }

    helper.sendMessage(buszlista, socket);
}

void RFSzerver::handleSoforlistaRequest(QTcpSocket *socket)
{
    std::map<int, std::string> soforok;
    soforok[1] = "Jozsi";

    protocol::SoforLista soforlista;

    for (std::map<int, std::string>::iterator i = soforok.begin(); i != soforok.end(); ++i) {
        protocol::Sofor *s = soforlista.add_soforok();

        s->set_id(i->first);
        s->set_nev(i->second);
    }

    helper.sendMessage(soforlista, socket);
}

void RFSzerver::handleUtvonalBuszSoforRequest(QTcpSocket *socket)
{
    //protocol::UtvonalBuszSoforRequest req;
    //helper.readMessage(req, socket);
    //qDebug() << "req read";

    protocol::UtvonalBuszSoforResponse resp;
    resp.set_status("ok");
    helper.sendMessage(resp, socket);
    qDebug() << "resp sent";
}

void RFSzerver::handleMegalloListaRequest(QTcpSocket *socket)
{
    helper.sendMessage(MegalloDB::findAll(), socket);
}

void RFSzerver::handleMegalloUjRequest(QTcpSocket *socket)
{
    protocol::Megallo m;
    std::cout << "reading uj megallo\n";
    helper.readMessage(m, socket);

    MegalloDB::add(m);
}

void RFSzerver::handleMegalloTorlesRequest(QTcpSocket *socket)
{
    protocol::Megallo m;
    helper.wait(socket);
    helper.readMessage(m, socket);

    MegalloDB::del(m);
}

void RFSzerver::handleUtvonalUjRequest(QTcpSocket *socket)
{
    protocol::Utvonal u;
    helper.readMessage(u, socket);

    UtvonalDB::add(u);
}

void RFSzerver::handleUtvonalTorlesRequest(QTcpSocket *socket)
{
    protocol::Utvonal u;
    helper.wait(socket);
    helper.readMessage(u, socket);

    UtvonalDB::del(u);
}

void RFSzerver::handleShutdownRequest()
{
    UtvonalDB::save();
    MegalloDB::save();

    qDebug() << "kilepes";
    exit(0);
}
