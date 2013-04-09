#include "utvonal_controller.h"

#include <string>

#include "megallok_controller.h"

utvonal_controller::utvonal_controller(networkhelper *helper)
{
    this->helper = helper;
}

void utvonal_controller::run()
{
    std::string olvasott;

    while (olvasott != "0") {
        std::cout << "=== UTVONALAK KEZELESE ===\n";
        std::cout << "1. lista\n";
        std::cout << "2. uj utvonal osszeallitasa\n";
        std::cout << "3. utvonal torlese\n";
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

void utvonal_controller::lista()
{
    helper->sendMessageType(protocol::MessageType::UTVONALLISTA_REQUEST);
    helper->wait();

    protocol::UtvonalLista utvonalak;
    helper->readMessage(utvonalak);

    lista_kiiras(utvonalak);
}

void utvonal_controller::lista_kiiras(protocol::UtvonalLista utvonalak)
{
    for (int i = 0; i < utvonalak.utvonalak_size(); ++i) {
        protocol::Utvonal u = utvonalak.utvonalak().Get(i);

        std::cout << u.id() << "\t" << u.nev() << "\n";
    }
}

void utvonal_controller::uj()
{
    megallok_controller mc(helper);
    protocol::MegalloLista megallolista;
    protocol::Utvonal utvonal;
    std::string olvasott;

    utvonal.set_id(1);
    std::cout << "Utvonal neve (megsem: ures): ";
    std::cin >> olvasott;
    if (!olvasott.length()) return;
    utvonal.set_nev(olvasott);

    helper->sendMessageType(protocol::MessageType::MEGALLO_LISTA_REQUEST);
    helper->wait();
    helper->readMessage(megallolista);

    olvasott = "asdf";
    while (olvasott != "0") {
        mc.lista_kiiras(megallolista);
        std::cout << "megallo id (vege: 0, megsem: -1): ";
        std::cin >> olvasott;

        if (olvasott == "-1") return;

        if (olvasott != "0") {
            int i;
            for (i = 0; i < megallolista.megallok_size(); ++i) {
                protocol::Megallo m = megallolista.megallok().Get(i);

                if (m.id() == atoi(olvasott.c_str())) {
                    protocol::Megallo *um = utvonal.add_megallok();
                    um->set_id(m.id());
                    um->set_nev(m.nev());
                    std::cout << "felveve\n";
                }
            }
        }
    }

    helper->sendMessageType(protocol::MessageType::UTVONAL_UJ_REQUEST);
    helper->sendMessage(utvonal);
}

void utvonal_controller::torles()
{
    std::string id;

    lista();

    std::cout << "melyiket toroljem (megsem: ures): ";
    std::cin >> id;

    if (!id.length()) return;

    protocol::Utvonal u;
    u.set_id(atoi(id.c_str()));
    u.set_nev("");

    helper->sendMessageType(protocol::MessageType::UTVONAL_TORLES_REQUEST);
    helper->sendMessage(u);
}
