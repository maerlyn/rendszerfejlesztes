#ifndef BEOSZTAS_CONTROLLER_H
#define BEOSZTAS_CONTROLLER_H

#include "networkhelper.h"

class beosztas_controller
{
    networkhelper *helper;

    protocol::SoforLista szabadSoforok(protocol::Jarat jarat);
    protocol::BuszLista szabadBuszok(protocol::Jarat jarat);

public:
    beosztas_controller(networkhelper *helper);

    void run();
    void elkeszites();
    void napilista();
};

#endif // BEOSZTAS_CONTROLLER_H
