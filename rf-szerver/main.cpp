#include <QtCore/QCoreApplication>
#include <QTcpServer>

#include "../protobuf/rendszerfejlesztes.pb.h"

#include "rfszerver.h"

int main(int argc, char *argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  QCoreApplication a(argc, argv);

  RFSzerver sz;

  google::protobuf::ShutdownProtobufLibrary();
  return a.exec();
}
