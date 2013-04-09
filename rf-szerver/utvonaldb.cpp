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
