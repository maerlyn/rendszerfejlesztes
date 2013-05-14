#ifndef FELHASZNALODB_H
#define FELHASZNALODB_H

#include "../protobuf/rendszerfejlesztes.pb.h"

#include <string>

class FelhasznaloDB
{
    static protocol::FelhasznaloLista felhasznalok;
    FelhasznaloDB() {}

public:
    static void load();
    static void save();
    static protocol::FelhasznaloLista findAll();
    static void del(protocol::Felhasznalo f);
    static int nextId();
    static void add(protocol::Felhasznalo ujfelhasznalo);
    static std::string csoport(protocol::Felhasznalo felhasznalo);

};

#endif // FELHASZNALODB_H
