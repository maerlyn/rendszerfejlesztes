#ifndef BUSZOK_CONTROLLER_H
#define BUSZOK_CONTROLLER_H

#include "networkhelper.h"

class buszok_controller
{
    networkhelper *helper;

public:
    buszok_controller(networkhelper *helper);

    void run();
    void lista();
    void lista_kiiras(protocol::BuszLista &lista);
    void uj();
    void torles();
};

#endif // BUSZOK_CONTROLLER_H
