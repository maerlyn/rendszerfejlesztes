#include "rfkliens.h"

#include <iostream>
#include <string>

#include "../protobuf/rendszerfejlesztes.pb.h"
#include "megallok_controller.h"
#include "utvonal_controller.h"
#include "buszok_controller.h"
#include "soforok_controller.h"
#include "jaratok_controller.h"
#include "beosztas_controller.h"

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
        std::cout << "2. megallok kezelese\n";
        std::cout << "3. utvonalak kezelese\n";
        std::cout << "4. buszok kezelese\n";
        std::cout << "5. soforok kezelese\n";
        std::cout << "6. jaratok kezelese\n";
        std::cout << "7. beosztas kezelese\n";
        std::cout << std::endl;
        std::cout << "0. kilepes\n";
        std::cout << "VALASZ: ";
        std::cin >> s;

        valasz = atoi(s.c_str());

        switch (valasz) {
            case 1: utvonal_sofor_busz_hozzarendeles(); break;
            case 2: megallok_kezelese(); break;
            case 3: utvonalak_kezelese(); break;
            case 4: buszok_kezelese(); break;
            case 5: soforok_kezelese(); break;
            case 6: jaratok_kezelese(); break;
            case 7: beosztas_kezelese(); break;

            case 999: shutdown(); break;
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

void rfkliens::megallok_kezelese()
{
    megallok_controller mc(helper);
    mc.run();
}

void rfkliens::utvonalak_kezelese()
{
    utvonal_controller uc(helper);
    uc.run();
}

void rfkliens::buszok_kezelese()
{
    buszok_controller bc(helper);
    bc.run();
}

void rfkliens::soforok_kezelese()
{
    soforok_controller sc(helper);
    sc.run();
}

void rfkliens::jaratok_kezelese()
{
    jaratok_controller jc(helper);
    jc.run();
}

void rfkliens::beosztas_kezelese()
{
    beosztas_controller bc(helper);
    bc.run();
}

void rfkliens::shutdown()
{
    helper->sendMessageType(protocol::MessageType::SHUTDOWN);
    exit(0);
}
