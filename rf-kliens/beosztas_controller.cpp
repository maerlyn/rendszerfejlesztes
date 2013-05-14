#include "beosztas_controller.h"

#include <string>
#include <iostream>

#include "soforok_controller.h"
#include "buszok_controller.h"

beosztas_controller::beosztas_controller(networkhelper *helper)
{
    this->helper = helper;
}

void beosztas_controller::run()
{
    std::string olvasott = "";

    while (olvasott != "0") {
        std::cout << "=== BEOSZTASOK KEZELESE ===\n";
        std::cout << "1. beosztas osszeallitasa\n";
        std::cout << "2. napi beosztas listazasa\n";
        std::cout << "\n";
        std::cout << "0. vissza a fomenube\n";
        std::cout << "valasztas: ";

        std::cin >> olvasott;

        switch (atoi(olvasott.c_str())) {
        case 1:
            elkeszites();
            break;

        case 2:
            napilista();
            break;
        }
    }
}

void beosztas_controller::elkeszites()
{
    soforok_controller sc(helper);
    buszok_controller bc(helper);
    std::string olvasott;
    std::string datum;

    helper->sendMessageType(protocol::MessageType::JARAT_LISTA_REQUEST);
    protocol::JaratLista jaratok;
    helper->wait();
    helper->readMessage(jaratok);

    std::cout << "Datum: ";
    std::cin >> datum;

    for (int i = 0; i < jaratok.jaratok_size(); ++i) {
        protocol::Beosztas beosztas;
        beosztas.set_id(1);

        protocol::Jarat jarat = jaratok.jaratok().Get(i);
        beosztas.set_datum(datum.c_str());
        beosztas.set_jarat_id(jarat.id());

        std::cout << "-- jarat: " << jarat.indulasi_ido() << std::endl;

        protocol::SoforLista soforok = szabadSoforok(jarat);
        sc.lista_kiiras(soforok);
        std::cout << "sofor: ";
        std::cin >> olvasott;
        beosztas.set_sofor_id(atoi(olvasott.c_str()));

        protocol::BuszLista buszok = szabadBuszok(jarat);
        bc.lista_kiiras(buszok);
        std::cout << "busz: ";
        std::cin >> olvasott;
        beosztas.set_busz_id(atoi(olvasott.c_str()));

        helper->sendMessageType(protocol::MessageType::BEOSZTAS_UJ_REQUEST);
        helper->wait();
        helper->sendMessage(beosztas);
        //std::cout << beosztas.DebugString() << std::endl;
    }
}

void beosztas_controller::napilista()
{
    std::string olvasott;

    std::cout << "nap: ";
    std::cin >> olvasott;

    protocol::Beosztas b;
    b.set_id(1);
    b.set_jarat_id(1);
    b.set_busz_id(1);
    b.set_sofor_id(1);
    b.set_datum(olvasott.c_str());

    helper->sendMessageType(protocol::MessageType_Types_BEOSZTAS_NAPILISTA_REQUEST);
    helper->sendMessage(b);

    protocol::BeosztasLista napilista;
    helper->wait();
    helper->readMessage(napilista);

    std::cout << "jarat\tbusz\tsofor\n";
    for (int i = 0; i < napilista.beosztasok_size(); ++i) {
        b = napilista.beosztasok().Get(i);

        std::cout << b.jarat_id() << "\t" << b.busz_id() << "\t" << b.sofor_id() << "\n";
    }
}

protocol::SoforLista beosztas_controller::szabadSoforok(protocol::Jarat jarat)
{
    jarat = jarat;
    protocol::SoforLista soforok;
    helper->sendMessageType(protocol::MessageType::SOFORLISTA_REQUEST);
    helper->wait();
    helper->readMessage(soforok);

    return soforok;
}

protocol::BuszLista beosztas_controller::szabadBuszok(protocol::Jarat jarat)
{
    jarat = jarat;
    protocol::BuszLista buszok;
    helper->sendMessageType(protocol::MessageType::BUSZLISA_REQUEST);
    helper->wait();
    helper->readMessage(buszok);

    return buszok;
}
