//
// Created by paultal on 01.04.2026.
//

#ifndef LAB06_07_V2_REPO_H
#define LAB06_07_V2_REPO_H

#include <vector>
#include "../domain/produs.h"

class RepoProduse {
private:
    // int nextId = 1; // pentru a genera id-uri unice
    std::vector<Produs> produse;
public:
    void adauga(const Produs& p);
    void sterge(const int id);
    void modifica(const Produs& produsNou);
    std::vector<Produs> getAll() const;
};

#endif //LAB06_07_V2_REPO_H