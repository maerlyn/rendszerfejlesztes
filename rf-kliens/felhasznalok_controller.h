#ifndef FELHASZNALOK_CONTROLLER_H
#define FELHASZNALOK_CONTROLLER_H

#include "networkhelper.h"

class felhasznalok_controller
{
    networkhelper *helper;

public:
    felhasznalok_controller(networkhelper *helper);

    void run();
    void lista();
    void lista_kiiras(protocol::FelhasznaloLista &lista);
    void uj();
    void torles();
};

#endif // FELHASZNALOK_CONTROLLER_H
