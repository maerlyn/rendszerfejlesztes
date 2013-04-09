#include "megallok_controller.h"

#include <string>
#include <iostream>

megallok_controller::megallok_controller(networkhelper *helper)
{
    this->helper = helper;
}

void megallok_controller::run()
{
    std::string olvasott = "";

    while (olvasott != "0") {
        std::cout << "=== MEGALLOK KEZELESE ===\n";
        std::cout << "1. lista\n";
        std::cout << "2. uj megallo\n";
        std::cout << "3. megallo torlese\n";
        std::cout << "\n";
        std::cout << "0. vissza a fomenube\n";
        std::cout << "valasztas: ";

        std::cin >> olvasott;

        switch (atoi(olvasott.c_str())) {
        case 1:
            lista();
            break;

        case 2:
            uj();
            break;

        case 3:
            torles();
            break;
        }
    }
}

void megallok_controller::lista()
{
    helper->sendMessageType(protocol::MessageType::MEGALLO_LISTA_REQUEST);
    protocol::MegalloLista megallok;
    helper->wait();

    helper->readMessage(megallok);
    lista_kiiras(megallok);
}

void megallok_controller::lista_kiiras(protocol::MegalloLista &lista)
{
    for (int i = 0; i < lista.megallok_size(); ++i) {
        protocol::Megallo u = lista.megallok().Get(i);
        std::cout << u.id() << "\t" << u.nev() << "\n";
    }
}

void megallok_controller::uj()
{
    std::string nev;

    std::cout << "Uj megallo neve (megsem: ures): ";
    std::cin >> nev;

    if (nev.length() == 0) return;

    protocol::Megallo ujmegallo;
    ujmegallo.set_id(1);
    ujmegallo.set_nev(nev);
    std::cout << ujmegallo.DebugString() << std::endl;

    helper->sendMessageType(protocol::MessageType::MEGALLO_UJ_REQUEST);
    helper->sendMessage(ujmegallo);
    helper->wait();
}

void megallok_controller::torles()
{
    std::string id;

    lista();

    std::cout << "Melyiket torlod (megse: 0): ";
    std::cin >> id;

    protocol::Megallo m;
    m.set_id(atoi(id.c_str()));
    m.set_nev("");

    helper->sendMessageType(protocol::MessageType::MEGALLO_TORLES_REQUEST);
    helper->sendMessage(m);
    helper->wait();
}
