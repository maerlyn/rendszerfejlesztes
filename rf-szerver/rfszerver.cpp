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
#include "buszdb.h"
#include "sofordb.h"
#include "jaratdb.h"
#include "beosztasdb.h"
#include "felhasznalodb.h"
#include "betegsegdb.h"

RFSzerver::RFSzerver(QObject *parent) : QObject(parent)
{
  QObject::connect(&(helper.socket), SIGNAL(newConnection()), this, SLOT(incomingConnection()));

  UtvonalDB::load();
  MegalloDB::load();
  BuszDB::load();
  SoforDB::load();
  JaratDB::load();
  BeosztasDB::load();
  FelhasznaloDB::load();
  BetegsegDB::load();
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

    case protocol::MessageType::UTVONAL_REQUEST:
      handleUtvonalRequest(sock);
      break;

    case protocol::MessageType::BUSZ_UJ_REQUEST:
      handleBuszUjRequest(sock);
      break;

    case protocol::MessageType::BUSZ_TORLES_REQUEST:
      handleBuszTorlesRequest(sock);
      break;

    case protocol::MessageType::SOFOR_UJ_REQUEST:
      handleSoforUjRequest(sock);
      break;

    case protocol::MessageType::SOFOR_TORLES_REQUEST:
      handleSoforTorlesRequest(sock);
      break;

    case protocol::MessageType::JARAT_LISTA_REQUEST:
      handleJaratListaRequest(sock);
      break;

    case protocol::MessageType::JARAT_UJ_REQUEST:
      handleJaratUjRequest(sock);
      break;

    case protocol::MessageType::JARAT_TORLES_REQUEST:
      handleJaratTorlesRequest(sock);
      break;

    case protocol::MessageType::BEOSZTAS_UJ_REQUEST:
      handleBeosztasUjRequest(sock);
      break;

    case protocol::MessageType::BEOSZTAS_NAPILISTA_REQUEST:
      handleBeosztasNapilistaRequest(sock);
      break;

    case protocol::MessageType::BEOSZTAS_NAPITORLES_REQUEST:
      handleBeosztasNapitorlesRequest(sock);
      break;

    case protocol::MessageType::FELHASZNALO_LISTA_REQUEST:
      handleFelhasznaloListaRequest(sock);
      break;

    case protocol::MessageType::FELHASZNALO_UJ_REQUEST:
      handleFelhasznaloUjRequest(sock);
      break;

    case protocol::MessageType::FELHASZNALO_TORLES_REQUEST:
      handleFelhasznaloTorlesRequest(sock);
      break;

    case protocol::MessageType::BETEGSEG_LISTA_REQUEST:
      handleBetegsegListaRequest(sock);
      break;

    case protocol::MessageType::BETEGSEG_UJ_REQUEST:
      handleBetegsegUjRequest(sock);
      break;

    case protocol::MessageType::BETEGSEG_TORLES_REQUEST:
      handleBetegsegTorlesRequest(sock);
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

    protocol::Felhasznalo f;
    f.set_felhasznalonev(arq.username());
    f.set_jelszo(arq.password());
    std::string csoport = FelhasznaloDB::csoport(f);

    arp.set_status(csoport != "" ? "ok" : "fail");
    arp.set_csoport(csoport);

    helper.sendMessage(arp, sock);
}

void RFSzerver::handleUtvonallistaRequest(QTcpSocket *sock)
{
    helper.sendMessage(UtvonalDB::findAll(), sock);
}

void RFSzerver::handleBuszlistaRequest(QTcpSocket *socket)
{
    helper.sendMessage(BuszDB::findAll(), socket);
}

void RFSzerver::handleSoforlistaRequest(QTcpSocket *socket)
{
    helper.sendMessage(SoforDB::findAll(), socket);
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

void RFSzerver::handleUtvonalRequest(QTcpSocket *socket)
{
    protocol::Utvonal u;
    //helper.wait(socket);
    helper.readMessage(u, socket);
    qDebug() << "keresunk utvonalat, id="+u.id();
    u = UtvonalDB::find(u.id());
    qDebug() << "talaltunk utvonalat";

    helper.sendMessage(u, socket);
}

void RFSzerver::handleBuszUjRequest(QTcpSocket *socket)
{
    protocol::Busz b;
    helper.wait(socket);
    helper.readMessage(b, socket);

    BuszDB::add(b);
}

void RFSzerver::handleBuszTorlesRequest(QTcpSocket *socket)
{
    protocol::Busz b;
    helper.wait(socket);
    helper.readMessage(b, socket);

    BuszDB::del(b);
}

void RFSzerver::handleSoforUjRequest(QTcpSocket *socket)
{
    protocol::Sofor s;
    helper.wait(socket);
    helper.readMessage(s, socket);

    SoforDB::add(s);
}

void RFSzerver::handleSoforTorlesRequest(QTcpSocket *socket)
{
    protocol::Sofor s;
    helper.wait(socket);
    helper.readMessage(s, socket);

    SoforDB::del(s);
}

void RFSzerver::handleJaratListaRequest(QTcpSocket *socket)
{
    helper.sendMessage(JaratDB::findAll(), socket);
}

void RFSzerver::handleJaratUjRequest(QTcpSocket *socket)
{
    protocol::Jarat j;
    helper.wait(socket);
    helper.readMessage(j, socket);

    JaratDB::add(j);
}

void RFSzerver::handleJaratTorlesRequest(QTcpSocket *socket)
{
    protocol::Jarat j;
    helper.wait(socket);
    helper.readMessage(j, socket);

    JaratDB::del(j);
}

void RFSzerver::handleBeosztasUjRequest(QTcpSocket *socket)
{
    protocol::Beosztas b;
    helper.wait(socket);
    helper.readMessage(b, socket);

    BeosztasDB::add(b);
}

void RFSzerver::handleBeosztasNapilistaRequest(QTcpSocket *socket)
{
    protocol::Beosztas b;
    helper.wait(socket);
    helper.readMessage(b, socket);

    protocol::BeosztasLista lista = BeosztasDB::napiLista(b.datum());

    helper.sendMessage(lista, socket);
}

void RFSzerver::handleBeosztasNapitorlesRequest(QTcpSocket *socket)
{
    protocol::Beosztas b;
    helper.wait(socket);
    helper.readMessage(b, socket);

    BeosztasDB::napiTorles(b.datum());
}

void RFSzerver::handleFelhasznaloListaRequest(QTcpSocket *socket)
{
    helper.sendMessage(FelhasznaloDB::findAll(), socket);
}

void RFSzerver::handleFelhasznaloUjRequest(QTcpSocket *socket)
{
    protocol::Felhasznalo f;
    helper.wait(socket);
    helper.readMessage(f, socket);

    FelhasznaloDB::add(f);
}

void RFSzerver::handleFelhasznaloTorlesRequest(QTcpSocket *socket)
{
    protocol::Felhasznalo f;
    helper.wait(socket);
    helper.readMessage(f, socket);

    FelhasznaloDB::del(f);
}

void RFSzerver::handleBetegsegListaRequest(QTcpSocket *socket)
{
    helper.sendMessage(BetegsegDB::findAll(), socket);
}

void RFSzerver::handleBetegsegUjRequest(QTcpSocket *socket)
{
    protocol::Betegseg b;
    helper.wait(socket);
    helper.readMessage(b, socket);

    BetegsegDB::add(b);
}

void RFSzerver::handleBetegsegTorlesRequest(QTcpSocket *socket)
{
    BetegsegDB::clear();
}

void RFSzerver::handleShutdownRequest()
{
    UtvonalDB::save();
    MegalloDB::save();
    BuszDB::save();
    SoforDB::save();
    JaratDB::save();
    BeosztasDB::save();
    FelhasznaloDB::save();
    BetegsegDB::save();

    qDebug() << "kilepes";
    exit(0);
}
