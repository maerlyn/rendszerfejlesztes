#include <QtCore/QCoreApplication>

#include <QHostAddress>
#include <QTcpSocket>
#include <string>
#include <iostream>
#include <termios.h>

#include "../protobuf/rendszerfejlesztes.pb.h"

int main(int argc, char *argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  QCoreApplication a(argc, argv);

  QTcpSocket sock;
  sock.connectToHost(QHostAddress::LocalHost, 7462);
  sock.waitForConnected();

  protocol::AuthRequest arq;
  std::string s;
  std::cout << "User: "; getline(std::cin, s);
  arq.set_username(s);

  /*termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  termios newt = oldt;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);*/
  std::cout << "Pass: "; getline(std::cin, s);
  arq.set_password(s);
  /*tcsetattr(STDIN_FILENO, TCSANOW, &oldt);*/

  arq.SerializeToString(&s);

  unsigned int length = s.length();
  sock.write((char*) &length, sizeof(length));
  sock.write(s.c_str());
  sock.flush();

  //std::cout << "waiting for response..." << std::endl;
  sock.waitForReadyRead(100);
  protocol::AuthResponse arp;

  //std::cout << "bytes avail: " << sock.bytesAvailable() << std::endl;
  sock.read((char*)&length, 4);
  //std::cout << "resp len: " << length << std::endl;
  QByteArray buf;
  buf = sock.read(length);
  arp.ParseFromString(QString(buf).toStdString());
  std::cout << arp.status() << std::endl;

  sock.read((char*) &length, 4);
  //std::cout << "length: " << length << "\n";
  buf = sock.read(length);
  protocol::MegalloLista ml;
  ml.ParseFromString(QString(buf).toStdString());

  //std::cout << "megallok.size(): " << ml.megallok().size() << " / " << ml.megallok_size() << "\n";
  for (int i = 0; i < ml.megallok().size(); ++i) {
      std::cout << ml.megallok().Get(i).nev() << "\n";
  }

  sock.disconnect();

  google::protobuf::ShutdownProtobufLibrary();
  exit(0);
  return a.exec();
}
