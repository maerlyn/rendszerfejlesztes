#include "networkhelper.h"

#include <string>
#include <QByteArray>

networkhelper::networkhelper()
{
    socket.connectToHost(QHostAddress::LocalHost, 7462);
    socket.waitForConnected();
}

void networkhelper::sendMessageType(protocol::MessageType_Types type)
{
    protocol::MessageType mt;
    mt.set_type(type);
    sendMessage(mt);
}

void networkhelper::wait()
{
    socket.waitForReadyRead(1000);
}
