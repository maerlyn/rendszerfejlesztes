#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QHostAddress>
#include <QTcpSocket>
#include <QTcpServer>
#include <QObject>
#include <QDebug>
#include <QString>
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
        int retries = 10;

        while (retries > 0) {
            sock->read((char*)&length, 4);

            if (length == 0) {
                --retries;
                sock->waitForReadyRead(10000);
            } else {
                buf = sock->read(length);
                qDebug() << QString("ez jott (l = %1)").arg(length); qDebug() << buf;
                message.ParseFromString(QString(buf).toStdString());
                return;
            }
        }

    }
};

#endif // NETWORKHELPER_H
