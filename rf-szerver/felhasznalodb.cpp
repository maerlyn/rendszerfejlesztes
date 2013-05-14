#include "felhasznalodb.h"

#include <iostream>
#include <fstream>

protocol::FelhasznaloLista FelhasznaloDB::felhasznalok;

void FelhasznaloDB::load()
{
    std::ifstream input("felhasznalok.db");

    FelhasznaloDB::felhasznalok.Clear();
    FelhasznaloDB::felhasznalok.ParseFromIstream(&input);

    std::cout << "felhasznalok betoltve\n";
}

void FelhasznaloDB::save()
{
    std::ofstream output("felhasznalok.db");

    FelhasznaloDB::felhasznalok.SerializePartialToOstream(&output);

    std::cout << "felhasznalok mentve\n";
}

protocol::FelhasznaloLista FelhasznaloDB::findAll()
{
    return felhasznalok;
}

int FelhasznaloDB::nextId()
{
    int ret = 0;

    for (int i = 0; i < felhasznalok.felhasznalok_size(); ++i) {
        protocol::Felhasznalo f = felhasznalok.felhasznalok().Get(i);

        if (f.id() > ret) ret = f.id();
    }

    return ret+1;
}

void FelhasznaloDB::add(protocol::Felhasznalo ujfelhasznalo)
{
    int id;

    id = nextId();
    std::cout << "FelhasznaloDB::add, id: " << id << std::endl;
    ujfelhasznalo.set_id(id);

    protocol::Felhasznalo *f = felhasznalok.add_felhasznalok();
    f->CopyFrom(ujfelhasznalo);
    //std::cout << m->DebugString() << "\n";
}

void FelhasznaloDB::del(protocol::Felhasznalo felhasznalo)
{
    for (int i = 0; i < felhasznalok.felhasznalok().size(); ++i) {
        if (felhasznalok.felhasznalok().Get(i).id() == felhasznalo.id()) {
            felhasznalok.mutable_felhasznalok()->SwapElements(i, felhasznalok.felhasznalok_size() - 1);
            felhasznalok.mutable_felhasznalok()->RemoveLast();
        }
    }
}

std::string FelhasznaloDB::csoport(protocol::Felhasznalo felhasznalo)
{
    for (int i = 0; i < felhasznalok.felhasznalok().size(); ++i) {
        protocol::Felhasznalo f = felhasznalok.felhasznalok().Get(i);

        if (f.felhasznalonev() == felhasznalo.felhasznalonev() && f.jelszo() == felhasznalo.jelszo()) {
            return f.csoport();
        }
    }

    return "";
}
