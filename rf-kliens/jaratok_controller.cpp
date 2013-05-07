#include "jaratok_controller.h"

#include <string>
#include <iostream>

#include "utvonal_controller.h"

jaratok_controller::jaratok_controller(networkhelper *helper)
{
    this->helper = helper;
}

void jaratok_controller::run()
{
    std::string olvasott = "";

    while (olvasott != "0") {
        std::cout << "=== JARATOK KEZELESE ===\n";
        std::cout << "1. lista\n";
        std::cout << "2. uj jarat\n";
        std::cout << "3. jarat torlese\n";
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

void jaratok_controller::lista()
{
    helper->sendMessageType(protocol::MessageType::JARAT_LISTA_REQUEST);
    protocol::JaratLista jaratok;
    helper->wait();

    helper->readMessage(jaratok);
    lista_kiiras(jaratok);
}

void jaratok_controller::lista_kiiras(protocol::JaratLista &lista)
{
    for (int i = 0; i < lista.jaratok_size(); ++i) {
        protocol::Jarat j = lista.jaratok().Get(i);

        helper->sendMessageType(protocol::MessageType::UTVONAL_REQUEST);
        protocol::Utvonal u; u.set_id(j.utvonal_id()); u.set_nev("");
        helper->sendMessage(u);
        helper->wait();
        helper->readMessage(u);

        std::cout << j.id() << "\t" << j.indulasi_ido() << "\t" << u.nev() << "\n";
    }
}

void jaratok_controller::uj()
{
    std::string indulasi_ido;
    std::string utvonal_id;
    utvonal_controller uc(helper);

    std::cout << "Uj jarat indulasi ideje (megsem: ures): ";
    std::cin >> indulasi_ido;

    if (indulasi_ido.length() == 0) return;

    uc.lista();
    std::cout << "Uj jarat utvonala (megsem: ures): ";
    std::cin >> utvonal_id;

    if (utvonal_id.length() == 0) return;

    protocol::Jarat ujjarat;
    ujjarat.set_id(1);
    ujjarat.set_indulasi_ido(indulasi_ido);
    ujjarat.set_utvonal_id(atoi(utvonal_id.c_str()));
    //std::cout << ujbusz.DebugString() << std::endl;

    helper->sendMessageType(protocol::MessageType::JARAT_UJ_REQUEST);
    helper->sendMessage(ujjarat);
    helper->wait();
}

void jaratok_controller::torles()
{
    std::string id;

    lista();

    std::cout << "Melyiket torlod (megse: 0): ";
    std::cin >> id;

    protocol::Jarat j;
    j.set_id(atoi(id.c_str()));
    j.set_indulasi_ido("");
    j.set_utvonal_id(1);

    helper->sendMessageType(protocol::MessageType::JARAT_TORLES_REQUEST);
    helper->sendMessage(j);
    helper->wait();
}
