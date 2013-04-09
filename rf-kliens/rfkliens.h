#ifndef RFKLIENS_H
#define RFKLIENS_H

#include <networkhelper.h>

class rfkliens
{
    networkhelper *helper;
public:
    rfkliens(networkhelper& helper);

    bool login();
    void menu();
    void utvonal_sofor_busz_hozzarendeles();
    void megallok_kezelese();

    void shutdown();
};

#endif // RFKLIENS_H
