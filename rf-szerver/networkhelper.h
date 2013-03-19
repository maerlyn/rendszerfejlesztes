#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include <iostream>
#include "../protobuf/rendszerfejlesztes.pb.h"

class networkhelper : QObject
{
    Q_OBJECT
public:
    QTcpServer socket;

    networkhelper();
    ~networkhelper() {}
    protocol::MessageType_Types readMessageType(QTcpSocket *sock);
    void wait(QTcpSocket *sock);

    template<typename T> void sendMessage(T message, QTcpSocket *sock) {
        std::string s;
        unsigned int length;

        message.SerializeToString(&s);
        length = s.length();
        sock->write((char*) &length, 4);
        sock->write(s.c_str());
        //std::cout << "ezt kuldjuk (l = " << length << ") " << s << std::endl;
        sock->flush();
        sock->waitForReadyRead(100);
    }

    template<typename T> void readMessage(T &message, QTcpSocket *sock) {
        unsigned int length;
        QByteArray buf;

        sock->read((char*)&length, 4);
        buf = sock->read(length);
        //std::cout << "ez jott (l = " << length << ") "; qDebug() << buf << std::endl;
        message.ParseFromString(QString(buf).toStdString());

    }
};

#endif // NETWORKHELPER_H
