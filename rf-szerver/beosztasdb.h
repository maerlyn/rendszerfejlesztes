#ifndef BEOSZTASDB_H
#define BEOSZTASDB_H

#include <string>
#include "../protobuf/rendszerfejlesztes.pb.h"

class BeosztasDB
{
    static protocol::BeosztasLista beosztasok;
    BeosztasDB() {}

public:
    static void load();
    static void save();
    static protocol::BeosztasLista findAll();
    static void del(protocol::Beosztas b);
    static int nextId();
    static void add(protocol::Beosztas ujbeosztas);
    static protocol::BeosztasLista napiLista(std::string datum);

};

#endif // BEOSZTASDB_H
