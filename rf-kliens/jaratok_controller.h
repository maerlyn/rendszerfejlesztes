#ifndef JARATOK_CONTROLLER_H
#define JARATOK_CONTROLLER_H

#include "networkhelper.h"

class jaratok_controller
{
    networkhelper *helper;

public:
    jaratok_controller(networkhelper *helper);

    void run();
    void lista();
    void lista_kiiras(protocol::JaratLista &lista);
    void uj();
    void torles();
};

#endif // JARATOK_CONTROLLER_H
