//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_REPOPRODUSE_H
#define LAB07_REPOPRODUSE_H
#include "../utils/CustomVector.h"
#include "../domain/Produs.h"


class RepoProduse
{
private:
    CustomVector<Produs> produse;

public:
    RepoProduse() = default;

    void add(Produs &p);
    void sterge(const int id);
    CustomVector<Produs>& getAll();
};


#endif //LAB07_REPOPRODUSE_H