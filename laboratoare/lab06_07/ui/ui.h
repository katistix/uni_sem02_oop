#ifndef UI_H
#define UI_H

#include "../service/service.h"

class UI {
private:
    ServiceProduse& service;
public:
    UI(ServiceProduse& service) : service(service) {}
    void run();
};

#endif