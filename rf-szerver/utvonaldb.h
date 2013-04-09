#ifndef UTVONALDB_H
#define UTVONALDB_H

#include "../protobuf/rendszerfejlesztes.pb.h"

class UtvonalDB
{
    static protocol::UtvonalLista utvonalak;
    UtvonalDB() {}

public:
    static void load();
    static void save();
    static protocol::UtvonalLista findAll();
    static void del(protocol::Utvonal u);
    static int nextId();
    static void add(protocol::Utvonal ujutvonal);

};

#endif // UTVONALDB_H
