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
};

#endif // UTVONALDB_H
