#include <QtCore/QCoreApplication>

#include <string>
#include <iostream>

#include "../protobuf/rendszerfejlesztes.pb.h"
#include "networkhelper.h"
#include "rfkliens.h"

int main(int argc, char *argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  QCoreApplication a(argc, argv);
  networkhelper helper;
  rfkliens kliens(helper);

  if (kliens.login()) {
      std::cout << "Sikeres bejelentkezes\n";
      kliens.menu();
  }

  //std::cout << "megallok.size(): " << ml.megallok().size() << " / " << ml.megallok_size() << "\n";
  //for (int i = 0; i < ml.megallok().size(); ++i) {
  //    std::cout << ml.megallok().Get(i).nev() << "\n";
  //}

  google::protobuf::ShutdownProtobufLibrary();
  exit(0);
  return a.exec();
}
