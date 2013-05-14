#ifndef RFKLIENS_H
#define RFKLIENS_H

#include <networkhelper.h>
#include <string>

class rfkliens
{
    networkhelper *helper;
    std::string csoport, felhasznalonev;

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
    void beosztas_kezelese();
    void felhasznalok_kezelese();
    void betegsegek_torlese();
    void betegseg_bejelentese();

    void shutdown();
};

#endif // RFKLIENS_H
