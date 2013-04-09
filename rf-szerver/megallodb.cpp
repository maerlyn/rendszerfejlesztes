#include "megallodb.h"

#include <iostream>
#include <fstream>

protocol::MegalloLista MegalloDB::megallok;

void MegalloDB::load()
{
    std::ifstream input("megallok.db");

    megallok.Clear();
    megallok.ParseFromIstream(&input);

    std::cout << "megallok betoltve\n";
}

void MegalloDB::save()
{
    std::ofstream output("megallok.db");

    megallok.SerializePartialToOstream(&output);

    std::cout << "megallok mentve\n";
}

protocol::MegalloLista MegalloDB::findAll()
{
    return megallok;
}

int MegalloDB::nextId()
{
    int ret = 0;

    for (int i = 0; i < megallok.megallok_size(); ++i) {
        protocol::Megallo m = megallok.megallok().Get(i);

        if (m.id() > ret) ret = m.id();
    }

    return ret+1;
}

void MegalloDB::add(protocol::Megallo ujmegallo)
{
    int id;

    id = nextId();
    std::cout << "MegalloDB::add, id: " << id << std::endl;

    protocol::Megallo *m = megallok.add_megallok();
    m->set_id(id);
    m->set_nev(ujmegallo.nev());
    //std::cout << m->DebugString() << "\n";
}

void MegalloDB::del(protocol::Megallo megallo)
{
    for (int i = 0; i < megallok.megallok().size(); ++i) {
        if (megallok.megallok().Get(i).id() == megallo.id()) {
            megallok.mutable_megallok()->SwapElements(i, megallok.megallok_size() - 1);
            megallok.mutable_megallok()->RemoveLast();
        }
    }
}
