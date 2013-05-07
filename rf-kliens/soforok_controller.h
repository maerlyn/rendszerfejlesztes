#ifndef SOFOROK_CONTROLLER_H
#define SOFOROK_CONTROLLER_H

#include "networkhelper.h"

class soforok_controller
{
    networkhelper *helper;

public:
    soforok_controller(networkhelper *helper);

    void run();
    void lista();
    void lista_kiiras(protocol::SoforLista &lista);
    void uj();
    void torles();
};

#endif // SOFOROK_CONTROLLER_H
