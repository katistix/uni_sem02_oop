//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_UI_H
#define LAB07_UI_H

#include "../service/ServiceProduse.h"

class UI
{
private:
    ServiceProduse &srv;


    static void printMenu();

    // commands
    void cmd_adauga();
    void cmd_show_all();
    void cmd_sterge();



public:
    explicit UI(ServiceProduse &srv) : srv(srv){}

    void run();
};


#endif //LAB07_UI_H