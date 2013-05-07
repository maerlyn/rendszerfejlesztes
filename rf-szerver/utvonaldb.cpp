#include "utvonaldb.h"

#include <iostream>
#include <fstream>

protocol::UtvonalLista UtvonalDB::utvonalak;

void UtvonalDB::load()
{
    std::ifstream input("utvonalak.db");

    UtvonalDB::utvonalak.Clear();
    UtvonalDB::utvonalak.ParseFromIstream(&input);

    std::cout << "utvonalak betoltve\n";
}

void UtvonalDB::save()
{
    std::ofstream output("utvonalak.db");

    UtvonalDB::utvonalak.SerializePartialToOstream(&output);

    std::cout << "utvonalak mentve\n";
}

protocol::UtvonalLista UtvonalDB::findAll()
{
    return utvonalak;
}

int UtvonalDB::nextId()
{
    int ret = 0;

    for (int i = 0; i < utvonalak.utvonalak_size(); ++i) {
        protocol::Utvonal m = utvonalak.utvonalak().Get(i);

        if (m.id() > ret) ret = m.id();
    }

    return ret+1;
}

void UtvonalDB::add(protocol::Utvonal ujutvonal)
{
    int id;

    id = nextId();
    std::cout << "UtvonalDB::add, id: " << id << std::endl;
    ujutvonal.set_id(id);

    protocol::Utvonal *u = utvonalak.add_utvonalak();
    u->CopyFrom(ujutvonal);
    //std::cout << m->DebugString() << "\n";
}

void UtvonalDB::del(protocol::Utvonal utvonal)
{
    for (int i = 0; i < utvonalak.utvonalak().size(); ++i) {
        if (utvonalak.utvonalak().Get(i).id() == utvonal.id()) {
            utvonalak.mutable_utvonalak()->SwapElements(i, utvonalak.utvonalak_size() - 1);
            utvonalak.mutable_utvonalak()->RemoveLast();
        }
    }
}
