#include "felhasznalok_controller.h"

#include <string>
#include <iostream>

felhasznalok_controller::felhasznalok_controller(networkhelper *helper)
{
    this->helper = helper;
}

void felhasznalok_controller::run()
{
    std::string olvasott = "";

    while (olvasott != "0") {
        std::cout << "=== FELHASZNALOK KEZELESE ===\n";
        std::cout << "1. lista\n";
        std::cout << "2. uj felhasznalo\n";
        std::cout << "3. felhasznalok torlese\n";
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

void felhasznalok_controller::lista()
{
    helper->sendMessageType(protocol::MessageType::FELHASZNALO_LISTA_REQUEST);
    protocol::FelhasznaloLista felhasznalok;
    helper->wait();

    helper->readMessage(felhasznalok);
    lista_kiiras(felhasznalok);
}

void felhasznalok_controller::lista_kiiras(protocol::FelhasznaloLista &lista)
{
    for (int i = 0; i < lista.felhasznalok_size(); ++i) {
        protocol::Felhasznalo f = lista.felhasznalok().Get(i);
        std::cout << f.id() << "\t" << f.felhasznalonev() << "\n";
    }
}

void felhasznalok_controller::uj()
{
    std::string felhasznalonev, jelszo, csoport;

    std::cout << "Uj felhasznalo neve (megsem: ures): ";
    std::cin >> felhasznalonev;
    if (felhasznalonev.length() == 0) return;

    std::cout << "Uj felhasznalo jelszava (megsem: ures): ";
    std::cin >> jelszo;
    if (jelszo.length() == 0) return;

    std::cout << "Uj felhasznalo csoportja (megsem: ures): ";
    std::cin >> csoport;
    if (csoport.length() == 0) return;

    protocol::Felhasznalo ujfelhasznalo;
    ujfelhasznalo.set_id(1);
    ujfelhasznalo.set_felhasznalonev(felhasznalonev);
    ujfelhasznalo.set_jelszo(jelszo);
    ujfelhasznalo.set_csoport(csoport);
    //std::cout << ujbusz.DebugString() << std::endl;

    helper->sendMessageType(protocol::MessageType::FELHASZNALO_UJ_REQUEST);
    helper->sendMessage(ujfelhasznalo);
    helper->wait();
}

void felhasznalok_controller::torles()
{
    std::string id;

    lista();

    std::cout << "Melyiket torlod (megse: 0): ";
    std::cin >> id;

    protocol::Felhasznalo f;
    f.set_id(atoi(id.c_str()));
    f.set_felhasznalonev("");
    f.set_jelszo("");
    f.set_csoport("");

    helper->sendMessageType(protocol::MessageType::FELHASZNALO_TORLES_REQUEST);
    helper->sendMessage(f);
    helper->wait();
}
