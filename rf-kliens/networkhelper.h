#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QHostAddress>
#include <QTcpSocket>
#include <QDebug>
#include <iostream>
#include "../protobuf/rendszerfejlesztes.pb.h"

class networkhelper
{
    QTcpSocket socket;
public:
    networkhelper();
    void sendMessageType(protocol::MessageType_Types type);
    void wait();

    template<typename T> void sendMessage(T message) {
        std::string s;
        unsigned int length;

        message.SerializeToString(&s);

        length = s.length();
        socket.write((char*) &length, 4);
        socket.write(s.c_str());
        //std::cout << "ezt kuldjuk: (l = " << length << ") " << s << std::endl;
        socket.flush();
    }

    template<typename T> void readMessage(T &message) {
        unsigned int length;
        QByteArray buf;

        socket.read((char*)&length, 4);
        buf = socket.read(length);
        message.ParseFromString(QString(buf).toStdString());

    }
};

#endif // NETWORKHELPER_H
