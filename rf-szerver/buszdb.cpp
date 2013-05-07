#include "buszdb.h"

#include <iostream>
#include <fstream>

protocol::BuszLista BuszDB::buszok;

void BuszDB::load()
{
    std::ifstream input("buszok.db");

    BuszDB::buszok.Clear();
    BuszDB::buszok.ParseFromIstream(&input);

    std::cout << "buszok betoltve\n";
}

void BuszDB::save()
{
    std::ofstream output("buszok.db");

    BuszDB::buszok.SerializePartialToOstream(&output);

    std::cout << "buszok mentve\n";
}

protocol::BuszLista BuszDB::findAll()
{
    return buszok;
}

int BuszDB::nextId()
{
    int ret = 0;

    for (int i = 0; i < buszok.buszok_size(); ++i) {
        protocol::Busz b = buszok.buszok().Get(i);

        if (b.id() > ret) ret = b.id();
    }

    return ret+1;
}

void BuszDB::add(protocol::Busz ujbusz)
{
    int id;

    id = nextId();
    std::cout << "BuszDB::add, id: " << id << std::endl;
    ujbusz.set_id(id);

    protocol::Busz *b = buszok.add_buszok();
    b->CopyFrom(ujbusz);
    //std::cout << m->DebugString() << "\n";
}

void BuszDB::del(protocol::Busz busz)
{
    for (int i = 0; i < buszok.buszok().size(); ++i) {
        if (buszok.buszok().Get(i).id() == busz.id()) {
            buszok.mutable_buszok()->SwapElements(i, buszok.buszok_size() - 1);
            buszok.mutable_buszok()->RemoveLast();
        }
    }
}
