#ifndef MEGALLOK_CONTROLLER_H
#define MEGALLOK_CONTROLLER_H

#include "networkhelper.h"

class megallok_controller
{
    networkhelper *helper;

public:
    megallok_controller(networkhelper *helper);

    void run();
    void lista();
    void lista_kiiras(protocol::MegalloLista &lista);
    void uj();
    void torles();
};

#endif // MEGALLOK_CONTROLLER_H
