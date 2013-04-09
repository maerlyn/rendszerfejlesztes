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
};

#endif // MEGALLODB_H
