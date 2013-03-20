#include "rfkliens.h"

#include <iostream>
#include <string>
#include "../protobuf/rendszerfejlesztes.pb.h"

rfkliens::rfkliens(networkhelper& helper)
{
    this->helper = &helper;
}

bool rfkliens::login()
{
    protocol::AuthRequest arq;
    std::string s;
    std::cout << "User: "; getline(std::cin, s);
    arq.set_username(s);

    std::cout << "Pass: "; getline(std::cin, s);
    arq.set_password(s);
    helper->sendMessageType(protocol::MessageType_Types_AUTH_TYPE);
    helper->sendMessage(arq);

    helper->wait();

    //std::cout << "waiting for response..." << std::endl;
    protocol::AuthResponse arp;
    helper->readMessage(arp);
    std::cout << arp.status() << std::endl;

    return arp.status() == "ok";
}

void rfkliens::menu()
{
    std::string s;
    int valasz;

    do {
        std::cout << " ### MENU ###\n";
        std::cout << "1. utvonal-sofor-busz hozzarendeles\n";
        std::cout << std::endl;
        std::cout << "0. kilepes\n";
        std::cout << "VALASZ: ";
        std::cin >> s;

        valasz = atoi(s.c_str());

        switch (valasz) {
            case 1: utvonal_sofor_busz_hozzarendeles();
        }
    } while (valasz != 0);
}

void rfkliens::utvonal_sofor_busz_hozzarendeles()
{
    int utvonal;
    int sofor;
    int busz;
    std::string s;

    helper->sendMessageType(protocol::MessageType::UTVONALLISTA_REQUEST);
    protocol::UtvonalLista utvonallista;
    helper->wait();
    helper->readMessage(utvonallista);

    std::cout << "UTVONAL (0 kilep)\n";
    for (int i = 0; i < utvonallista.utvonalak().size(); ++i) {
        std::cout << utvonallista.utvonalak().Get(i).id() << ". " << utvonallista.utvonalak().Get(i).nev() << std::endl;
    }
    std::cout << "valasztas: "; std::cin >> s;
    if (s == "0") return;
    utvonal = atoi(s.c_str());

    helper->sendMessageType(protocol::MessageType::SOFORLISTA_REQUEST);
    protocol::SoforLista soforlista;
    helper->wait();
    helper->readMessage(soforlista);

    std::cout << "SOFOR (0 kilep)\n";
    for (int i = 0; i < soforlista.soforok().size(); ++i) {
        std::cout << soforlista.soforok().Get(i).id() << ". " << soforlista.soforok().Get(i).nev() << std::endl;
    }
    std::cout << "valasztas: "; std::cin >> s;
    if (s == "0") return;
    sofor = atoi(s.c_str());

    helper->sendMessageType(protocol::MessageType::BUSZLISA_REQUEST);
    protocol::BuszLista buszlista;
    helper->wait();
    helper->readMessage(buszlista);

    std::cout << "BUSZ (0 kilep)\n";
    for (int i = 0; i < buszlista.buszok().size(); ++i) {
        std::cout << buszlista.buszok().Get(i).id() << ". " << buszlista.buszok().Get(i).rendszam() << std::endl;
    }
    std::cout << "valasztas: "; std::cin >> s;
    if (s == "0") return;
    busz = atoi(s.c_str());

    protocol::UtvonalBuszSoforRequest ubsr;
    ubsr.set_utvonal_id(utvonal);
    ubsr.set_busz_id(busz);
    ubsr.set_sofor_id(sofor);
    std::cout << ubsr.DebugString();
    helper->sendMessageType(protocol::MessageType::UTVONAL_BUSZ_SOFOR_REQUEST);
    helper->wait();
    helper->sendMessage(ubsr);
    helper->wait();

    protocol::UtvonalBuszSoforResponse resp;
    std::cout << resp.status();
}
