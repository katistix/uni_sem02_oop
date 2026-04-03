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

    void add(const Produs &p);
    void sterge(int id);
    void update(const Produs &p) const;
    CustomVector<Produs>& getAll();
};


#endif //LAB07_REPOPRODUSE_H