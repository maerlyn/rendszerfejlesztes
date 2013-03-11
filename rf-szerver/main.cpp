#include <QtCore/QCoreApplication>
#include <QTcpServer>

#include "../protobuf/rendszerfejlesztes.pb.h"

#include "connection.h"
#include "rfszerver.h"

int main(int argc, char *argv[])
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  QCoreApplication a(argc, argv);

  if (!createConnection()) {
    qDebug() << "DB connection failed";
    exit(1);
  }

  RFSzerver sz;

  google::protobuf::ShutdownProtobufLibrary();
  return a.exec();
}
