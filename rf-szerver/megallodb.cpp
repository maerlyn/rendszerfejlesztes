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
