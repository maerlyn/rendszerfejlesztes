#ifndef UTVONAL_CONTROLLER_H
#define UTVONAL_CONTROLLER_H

#include "../protobuf/rendszerfejlesztes.pb.h"
#include "networkhelper.h"

class utvonal_controller
{
    networkhelper *helper;
public:
    utvonal_controller(networkhelper *helper);

    void run();
    void lista();
    void lista_kiiras(protocol::UtvonalLista utvonalak);
    void uj();
    void torles();
};

#endif // UTVONAL_CONTROLLER_H
