#include "networkhelper.h"

#include <string>
#include <QByteArray>

networkhelper::networkhelper() : QObject(0)
{
    qDebug() << socket.listen(QHostAddress::Any, 7462);
    if (!socket.isListening()) {
      exit(1);
    }

    //QObject::connect(&socket, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
}

protocol::MessageType_Types networkhelper::readMessageType(QTcpSocket *sock)
{
    protocol::MessageType mt;
    readMessage(mt, sock);
    return mt.type();
}

void networkhelper::wait(QTcpSocket *sock)
{
    sock->waitForReadyRead(10000);
}
