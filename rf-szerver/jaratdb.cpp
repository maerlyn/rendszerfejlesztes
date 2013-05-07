#include "jaratdb.h"

#include <iostream>
#include <fstream>

protocol::JaratLista JaratDB::jaratok;

void JaratDB::load()
{
    std::ifstream input("jaratok.db");

    JaratDB::jaratok.Clear();
    JaratDB::jaratok.ParseFromIstream(&input);

    std::cout << "jaratok betoltve\n";
}

void JaratDB::save()
{
    std::ofstream output("jaratok.db");

    JaratDB::jaratok.SerializePartialToOstream(&output);

    std::cout << "jaratok mentve\n";
}

protocol::JaratLista JaratDB::findAll()
{
    return jaratok;
}

int JaratDB::nextId()
{
    int ret = 0;

    for (int i = 0; i < jaratok.jaratok_size(); ++i) {
        protocol::Jarat j = jaratok.jaratok().Get(i);

        if (j.id() > ret) ret = j.id();
    }

    return ret+1;
}

void JaratDB::add(protocol::Jarat ujjarat)
{
    int id;

    id = nextId();
    std::cout << "JaratDB::add, id: " << id << std::endl;
    ujjarat.set_id(id);

    protocol::Jarat *j = jaratok.add_jaratok();
    j->CopyFrom(ujjarat);
    //std::cout << m->DebugString() << "\n";
}

void JaratDB::del(protocol::Jarat jarat)
{
    for (int i = 0; i < jaratok.jaratok().size(); ++i) {
        if (jaratok.jaratok().Get(i).id() == jarat.id()) {
            jaratok.mutable_jaratok()->SwapElements(i, jaratok.jaratok_size() - 1);
            jaratok.mutable_jaratok()->RemoveLast();
        }
    }
}
