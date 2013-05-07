#ifndef JARATDB_H
#define JARATDB_H

#include "../protobuf/rendszerfejlesztes.pb.h"

class JaratDB
{
    static protocol::JaratLista jaratok;
    JaratDB() {}

public:
    static void load();
    static void save();
    static protocol::JaratLista findAll();
    static void del(protocol::Jarat j);
    static int nextId();
    static void add(protocol::Jarat j);

};

#endif // JARATDB_H
