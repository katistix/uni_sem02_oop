//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_SERVICEPRODUSE_H
#define LAB07_SERVICEPRODUSE_H

#include "../repo/RepoProduse.h"
#include "../validators/ProdusValidator.h"


class ServiceProduse
{
private:
    RepoProduse &repo;
    ProdusValidator &validator;

public:
    ServiceProduse(RepoProduse &_repo, ProdusValidator &_val) : repo{_repo}, validator(_val){};

    void add(int id, char *nume, char *tip, double pret, char *producator);
    void sterge(int id) const;
    CustomVector<Produs>& getAllProduse() const;
};


#endif //LAB07_SERVICEPRODUSE_H