//
// Created by paultal on 02.04.2026.
//

#include "ServiceProduse.h"

void ServiceProduse::add(const int id, const char* nume, const char* tip, const double pret, const char* producator) const
{
    const Produs p(id, nume, tip, pret, producator);

    ProdusValidator::validate(p);

    this->repo.add(p);
}

void ServiceProduse::sterge(const int id) const
{
    this->repo.sterge(id);
}

void ServiceProduse::update(const int id, char* name, char* tip, const double pret, char* producator) const
{
    const Produs p(id, name, tip, pret, producator);

    ProdusValidator::validate(p);

    this->repo.update(p);
}

CustomVector<Produs>& ServiceProduse::getAllProduse() const
{
    return this->repo.getAll();
}

CustomVector<Produs> ServiceProduse::getSorted(const std::function<bool(const Produs&, const Produs&)>& cmp) const
{
    CustomVector<Produs> result;
    const CustomVector<Produs>& all = this->repo.getAll();
    // copiaza vectorul
    for (int i = 0; i < all.get_size();i++)
    {
        result.add(all.get_by_index(i));
    }

    // bubble sort on copy
    for (int i = 0; i < result.get_size(); i++)
    {
        for (int j = 0; j < result.get_size() - 1; j++)
        {
            if (cmp(result.get_by_index(j), result.get_by_index(j+1)))
            {
               // swap by value
                const Produs temp = result.get_by_index(j);
                result.get_by_index(j) = result.get_by_index(j+1);
                result.get_by_index(j+1) = temp;
            }
        }
    }

    return result;


}

CustomVector<Produs> ServiceProduse::getFiltered(const std::function<bool(const Produs&)>& predicate) const
{
    CustomVector<Produs> result;
    const CustomVector<Produs>& all = this->repo.getAll();

    // append to the result only the elements that respect the condition
    for (int i = 0; i < all.get_size();i++)
    {
        if (predicate(all.get_by_index(i)))
        {
            result.add(all.get_by_index(i));
        }
    }

    return result;
}
