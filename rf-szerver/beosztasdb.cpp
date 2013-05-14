#include "beosztasdb.h"

#include <iostream>
#include <fstream>

protocol::BeosztasLista BeosztasDB::beosztasok;

void BeosztasDB::load()
{
    std::ifstream input("beosztasok.db");

    BeosztasDB::beosztasok.Clear();
    BeosztasDB::beosztasok.ParseFromIstream(&input);

    std::cout << "beosztasok betoltve\n";
}

void BeosztasDB::save()
{
    std::ofstream output("beosztasok.db");

    BeosztasDB::beosztasok.SerializePartialToOstream(&output);

    std::cout << "beosztasok mentve\n";
}

protocol::BeosztasLista BeosztasDB::findAll()
{
    return beosztasok;
}

int BeosztasDB::nextId()
{
    int ret = 0;

    for (int i = 0; i < beosztasok.beosztasok_size(); ++i) {
        protocol::Beosztas b = beosztasok.beosztasok().Get(i);

        if (b.id() > ret) ret = b.id();
    }

    return ret+1;
}

void BeosztasDB::add(protocol::Beosztas ujbeosztas)
{
    int id;

    id = nextId();
    std::cout << "BeosztasDB::add, id: " << id << std::endl;
    ujbeosztas.set_id(id);

    protocol::Beosztas *b = beosztasok.add_beosztasok();
    b->CopyFrom(ujbeosztas);
    //std::cout << m->DebugString() << "\n";
}

void BeosztasDB::del(protocol::Beosztas beosztas)
{
    for (int i = 0; i < beosztasok.beosztasok().size(); ++i) {
        if (beosztasok.beosztasok().Get(i).id() == beosztas.id()) {
            beosztasok.mutable_beosztasok()->SwapElements(i, beosztasok.beosztasok_size() - 1);
            beosztasok.mutable_beosztasok()->RemoveLast();
        }
    }
}

protocol::BeosztasLista BeosztasDB::napiLista(std::string datum)
{
    protocol::BeosztasLista ret;

    for (int i = 0; i < beosztasok.beosztasok_size(); ++i) {
        protocol::Beosztas b = beosztasok.beosztasok().Get(i);

        if (b.datum() == datum) {
            protocol::Beosztas *add = ret.add_beosztasok();
            add->CopyFrom(b);
        }
    }

    return ret;
}
