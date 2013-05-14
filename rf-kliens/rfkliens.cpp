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
#include "felhasznalok_controller.h"

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

    csoport = arp.csoport();
    felhasznalonev = arq.username();

    return arp.status() == "ok";
}

void rfkliens::menu()
{
    std::string s;
    int valasz;

    do {
        std::cout << " ### MENU ###\n";

        if (csoport == "diszpecser") {
            helper->sendMessageType(protocol::MessageType::BETEGSEG_LISTA_REQUEST);
            helper->wait();
            protocol::BetegsegLista betegsegek;
            helper->readMessage(betegsegek);
            std::cout << betegsegek.betegsegek_size() << "\n";
            if (betegsegek.betegsegek_size()) {
                std::cout << "++ betegsegek\n";
                std::cout << "ki\tmikortol\tmeddig\n";

                for (int i = 0; i < betegsegek.betegsegek_size(); ++i) {
                    protocol::Betegseg b = betegsegek.betegsegek().Get(i);

                    std::cout << b.felhasznalonev() << "\t" << b.mikortol() << "\t" << b.meddig() << "\n";
                }

                std::cout << std::endl;
            }
        }

        if (csoport == "sofor") {
            std::cout << "10. betegseg bejelentese\n";
        } else if (csoport == "titkar") {
            std::cout << "2. megallok kezelese\n";
            std::cout << "3. utvonalak kezelese\n";
            std::cout << "4. buszok kezelese\n";
            std::cout << "5. soforok kezelese\n";
            std::cout << "6. jaratok kezelese\n";
            std::cout << "8. felhasznalok kezelese\n";
        } else if (csoport == "diszpecser") {
            std::cout << "7. beosztas kezelese\n";
            std::cout << "9. betegsegek torlese\n";
        }

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
            case 8: felhasznalok_kezelese(); break;
            case 9: betegsegek_torlese(); break;
            case 10: betegseg_bejelentese(); break;

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

void rfkliens::felhasznalok_kezelese()
{
    felhasznalok_controller fc(helper);
    fc.run();
}

void rfkliens::betegsegek_torlese()
{
    helper->sendMessageType(protocol::MessageType::BETEGSEG_TORLES_REQUEST);
}

void rfkliens::betegseg_bejelentese()
{
    std::string mikortol, meddig;

    std::cout << "mikortol: ";
    std::cin >> mikortol;
    if (mikortol.length() == 0) return;

    std::cout << "meddig: ";
    std::cin >> meddig;
    if (meddig.length() == 0) return;

    protocol::Betegseg b;

    b.set_felhasznalonev(felhasznalonev);
    b.set_mikortol(mikortol);
    b.set_meddig(meddig);

    helper->sendMessageType(protocol::MessageType::BETEGSEG_UJ_REQUEST);
    helper->sendMessage(b);
}

void rfkliens::shutdown()
{
    helper->sendMessageType(protocol::MessageType::SHUTDOWN);
    exit(0);
}
