//
// Created by paultal on 01.04.2026.
//

#ifndef LAB06_07_V2_UI_H
#define LAB06_07_V2_UI_H

#include "../service/service.h"

class UI {
private:
    ServiceProduse& service;
public:
    explicit UI(ServiceProduse& service) : service(service) {}
    void run() const;
};

#endif //LAB06_07_V2_UI_H