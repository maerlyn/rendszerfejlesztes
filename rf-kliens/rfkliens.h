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
    void utvonalak_kezelese();
    void buszok_kezelese();
    void soforok_kezelese();
    void jaratok_kezelese();

    void shutdown();
};

#endif // RFKLIENS_H
