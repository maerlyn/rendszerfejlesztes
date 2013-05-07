#ifndef BUSZDB_H
#define BUSZDB_H

#include "../protobuf/rendszerfejlesztes.pb.h"

class BuszDB
{
    static protocol::BuszLista buszok;
    BuszDB() {}

public:
    static void load();
    static void save();
    static protocol::BuszLista findAll();
    static void del(protocol::Busz b);
    static int nextId();
    static void add(protocol::Busz busz);

};

#endif // BUSZDB_H
