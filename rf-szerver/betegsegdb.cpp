#include "betegsegdb.h"

#include <iostream>
#include <fstream>

protocol::BetegsegLista BetegsegDB::betegsegek;

void BetegsegDB::load()
{
    std::ifstream input("betegsegek.db");

    BetegsegDB::betegsegek.Clear();
    BetegsegDB::betegsegek.ParseFromIstream(&input);

    std::cout << "betegsegek betoltve\n";
}

void BetegsegDB::save()
{
    std::ofstream output("betegsegek.db");

    BetegsegDB::betegsegek.SerializePartialToOstream(&output);

    std::cout << "betegsegek mentve\n";
}

protocol::BetegsegLista BetegsegDB::findAll()
{
    return betegsegek;
}

void BetegsegDB::add(protocol::Betegseg ujbetegseg)
{
    protocol::Betegseg *b = betegsegek.add_betegsegek();
    b->CopyFrom(ujbetegseg);
    //std::cout << m->DebugString() << "\n";
}

void BetegsegDB::clear()
{
    betegsegek.Clear();
}
