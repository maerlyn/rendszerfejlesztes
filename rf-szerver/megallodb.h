#ifndef MEGALLODB_H
#define MEGALLODB_H

#include "../protobuf/rendszerfejlesztes.pb.h"

class MegalloDB
{
    static protocol::MegalloLista megallok;
    MegalloDB();
public:
    static void load();
    static void save();
    static protocol::MegalloLista findAll();
    static int nextId();
    static void add(protocol::Megallo ujmegallo);
    static void del(protocol::Megallo megallo);
};

#endif // MEGALLODB_H
