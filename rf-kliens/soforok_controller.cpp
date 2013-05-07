#include "soforok_controller.h"

#include <string>
#include <iostream>

soforok_controller::soforok_controller(networkhelper *helper)
{
    this->helper = helper;
}

void soforok_controller::run()
{
    std::string olvasott = "";

    while (olvasott != "0") {
        std::cout << "=== SOFOROK KEZELESE ===\n";
        std::cout << "1. lista\n";
        std::cout << "2. uj sofor\n";
        std::cout << "3. sofor torlese\n";
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

void soforok_controller::lista()
{
    helper->sendMessageType(protocol::MessageType::SOFORLISTA_REQUEST);
    protocol::SoforLista soforok;
    helper->wait();

    helper->readMessage(soforok);
    lista_kiiras(soforok);
}

void soforok_controller::lista_kiiras(protocol::SoforLista &lista)
{
    for (int i = 0; i < lista.soforok_size(); ++i) {
        protocol::Sofor s = lista.soforok().Get(i);
        std::cout << s.id() << "\t" << s.nev() << "\n";
    }
}

void soforok_controller::uj()
{
    std::string nev;

    std::cout << "Uj sofor neve (megsem: ures): ";
    std::cin >> nev;

    if (nev.length() == 0) return;

    protocol::Sofor ujsofor;
    ujsofor.set_id(1);
    ujsofor.set_nev(nev);
    //std::cout << ujbusz.DebugString() << std::endl;

    helper->sendMessageType(protocol::MessageType::SOFOR_UJ_REQUEST);
    helper->sendMessage(ujsofor);
    helper->wait();
}

void soforok_controller::torles()
{
    std::string id;

    lista();

    std::cout << "Melyiket torlod (megse: 0): ";
    std::cin >> id;

    protocol::Sofor b;
    b.set_id(atoi(id.c_str()));
    b.set_nev("");

    helper->sendMessageType(protocol::MessageType::SOFOR_TORLES_REQUEST);
    helper->sendMessage(b);
    helper->wait();
}
