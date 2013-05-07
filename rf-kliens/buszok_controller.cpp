#include "buszok_controller.h"

#include <string>
#include <iostream>

buszok_controller::buszok_controller(networkhelper *helper)
{
    this->helper = helper;
}

void buszok_controller::run()
{
    std::string olvasott = "";

    while (olvasott != "0") {
        std::cout << "=== BUSZOK KEZELESE ===\n";
        std::cout << "1. lista\n";
        std::cout << "2. uj busz\n";
        std::cout << "3. busz torlese\n";
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

void buszok_controller::lista()
{
    helper->sendMessageType(protocol::MessageType::BUSZLISA_REQUEST);
    protocol::BuszLista buszok;
    helper->wait();

    helper->readMessage(buszok);
    lista_kiiras(buszok);
}

void buszok_controller::lista_kiiras(protocol::BuszLista &lista)
{
    for (int i = 0; i < lista.buszok_size(); ++i) {
        protocol::Busz b = lista.buszok().Get(i);
        std::cout << b.id() << "\t" << b.rendszam() << "\n";
    }
}

void buszok_controller::uj()
{
    std::string rendszam;

    std::cout << "Uj busz rendszama (megsem: ures): ";
    std::cin >> rendszam;

    if (rendszam.length() == 0) return;

    protocol::Busz ujbusz;
    ujbusz.set_id(1);
    ujbusz.set_rendszam(rendszam);
    std::cout << ujbusz.DebugString() << std::endl;

    helper->sendMessageType(protocol::MessageType::BUSZ_UJ_REQUEST);
    helper->sendMessage(ujbusz);
    helper->wait();
}

void buszok_controller::torles()
{
    std::string id;

    lista();

    std::cout << "Melyiket torlod (megse: 0): ";
    std::cin >> id;

    protocol::Busz b;
    b.set_id(atoi(id.c_str()));
    b.set_rendszam("");

    helper->sendMessageType(protocol::MessageType::BUSZ_TORLES_REQUEST);
    helper->sendMessage(b);
    helper->wait();
}
