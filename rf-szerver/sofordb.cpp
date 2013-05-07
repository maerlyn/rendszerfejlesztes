#include "sofordb.h"

#include <iostream>
#include <fstream>

protocol::SoforLista SoforDB::soforok;

void SoforDB::load()
{
    std::ifstream input("soforok.db");

    SoforDB::soforok.Clear();
    SoforDB::soforok.ParseFromIstream(&input);

    std::cout << "soforok betoltve\n";
}

void SoforDB::save()
{
    std::ofstream output("soforok.db");

    SoforDB::soforok.SerializePartialToOstream(&output);

    std::cout << "soforok mentve\n";
}

protocol::SoforLista SoforDB::findAll()
{
    return soforok;
}

int SoforDB::nextId()
{
    int ret = 0;

    for (int i = 0; i < soforok.soforok_size(); ++i) {
        protocol::Sofor s = soforok.soforok().Get(i);

        if (s.id() > ret) ret = s.id();
    }

    return ret+1;
}

void SoforDB::add(protocol::Sofor ujsofor)
{
    int id;

    id = nextId();
    std::cout << "SoforDB::add, id: " << id << std::endl;
    ujsofor.set_id(id);

    protocol::Sofor *s = soforok.add_soforok();
    s->CopyFrom(ujsofor);
    //std::cout << m->DebugString() << "\n";
}

void SoforDB::del(protocol::Sofor sofor)
{
    for (int i = 0; i < soforok.soforok().size(); ++i) {
        if (soforok.soforok().Get(i).id() == sofor.id()) {
            soforok.mutable_soforok()->SwapElements(i, soforok.soforok_size() - 1);
            soforok.mutable_soforok()->RemoveLast();
        }
    }
}
