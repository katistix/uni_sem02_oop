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
    void cmd_adauga() const;
    void cmd_show_all() const;
    void cmd_sterge() const;
    void cmd_update() const;

    void cmd_sort() const;
    void cmd_filter() const;
    void cmd_load_dummy() const;



public:
    explicit UI(ServiceProduse &srv) : srv(srv){}

    void run() const;
};


#endif //LAB07_UI_H