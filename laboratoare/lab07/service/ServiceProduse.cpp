//
// Created by paultal on 02.04.2026.
//

#include "ServiceProduse.h"

void ServiceProduse::add(int id, char* nume, char* tip, double pret, char* producator)
{
    Produs p(id, nume, tip, pret, producator);

    this->validator.validate(p);

    this->repo.add(p);
}

void ServiceProduse::sterge(const int id) const
{
    this->repo.sterge(id);
}

CustomVector<Produs>& ServiceProduse::getAllProduse() const
{
    return this->repo.getAll();
}
