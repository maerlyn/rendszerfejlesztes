#ifndef BETEGSEGDB_H
#define BETEGSEGDB_H

#include "../protobuf/rendszerfejlesztes.pb.h"

class BetegsegDB
{
    static protocol::BetegsegLista betegsegek;
    BetegsegDB() {}

public:
    static void load();
    static void save();
    static protocol::BetegsegLista findAll();
    static void clear();
    static void add(protocol::Betegseg ujbetegseg);

};

#endif // BETEGSEGDB_H
