#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QtDebug>
#include <QStringList>

bool createConnection()
{
  qDebug() << "Loaded drivers" << QSqlDatabase::drivers();

  QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
  db.setDatabaseName("rendszerfejlesztes");
  db.setUserName("root");
  db.setPassword("root");
  db.setHostName("localhost");

  if (!db.open() ) {
    qDebug() << QObject::tr("Database Error: ") +
    db.lastError().driverText();
    qDebug() << db.lastError().databaseText();
    return false;
  }

  return true;
};

QString escape(const QString input)
{
  QByteArray arr = input.toAscii();
  QString output = "0x";
  QTextStream outstream(&output, QIODevice::WriteOnly);
  for (int i=0; i < arr.count(); ++i) {
    outstream << QString::number(arr.at(i), 16);
  }
  return output;
};

#endif
