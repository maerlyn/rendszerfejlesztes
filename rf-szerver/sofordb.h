#ifndef SOFORDB_H
#define SOFORDB_H

#include "../protobuf/rendszerfejlesztes.pb.h"

class SoforDB
{
    static protocol::SoforLista soforok;
    SoforDB() {}

public:
    static void load();
    static void save();
    static protocol::SoforLista findAll();
    static void del(protocol::Sofor s);
    static int nextId();
    static void add(protocol::Sofor ujsofor);

};

#endif // SOFORDB_H
