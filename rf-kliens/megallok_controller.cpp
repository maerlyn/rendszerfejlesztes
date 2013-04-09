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
        std::cout << "\n";
        std::cout << "0. vissza a fomenube\n";
        std::cout << "valasztas: ";

        std::cin >> olvasott;

        switch (atoi(olvasott.c_str())) {
        case 1:
            lista();
            break;
        }
    }
}

void megallok_controller::lista()
{
    helper->sendMessageType(protocol::MessageType::UTVONALLISTA_REQUEST);
    protocol::UtvonalLista utvonalak;
    helper->wait();

    helper->readMessage(utvonalak);
    lista_kiiras(utvonalak);
}

void megallok_controller::lista_kiiras(protocol::UtvonalLista &lista)
{
    for (int i = 0; i < lista.utvonalak_size(); ++i) {
        protocol::Utvonal u = lista.utvonalak().Get(i);
        std::cout << u.id() << "\t" << u.nev() << "\n";
    }
}
