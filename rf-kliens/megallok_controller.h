#ifndef MEGALLOK_CONTROLLER_H
#define MEGALLOK_CONTROLLER_H

#include "networkhelper.h"

class megallok_controller
{
    networkhelper *helper;

    void lista_kiiras(protocol::UtvonalLista &lista);
public:
    megallok_controller(networkhelper *helper);

    void run();
    void lista();
};

#endif // MEGALLOK_CONTROLLER_H
