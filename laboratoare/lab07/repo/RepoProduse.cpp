//
// Created by paultal on 02.04.2026.
//

#include "RepoProduse.h"
#include "../exceptions/RepositoryException.h"

void RepoProduse::add(const Produs& p)
{
    for (int i = 0; i < this->produse.get_size(); i++)
    {
        if (this->produse.get_by_index(i).getId() == p.getId())
            throw RepositoryException("Produsul cu acest ID exista deja!");
    }
    this->produse.add(p);
}

void RepoProduse::sterge(const int id)
{
    // cauta produsul cu id-ul cautat si sterge-l din vector,
    // daca nu exista arunca o eroare de repo
    bool found = false;
    for (int i=0; i<this->produse.get_size();i++)
    {
        if (produse.get_by_index(i).getId() == id)
        {
            produse.remove_index(i);
            found = true;
            break;
        }
    }

    if (!found)
    {
        throw RepositoryException("Nu exista produsul cu id-ul dat!");
    }
}

void RepoProduse::update(const Produs& p) const
{
    bool found = false;
    for (int i=0;i<this->produse.get_size();i++)
    {
        if (produse.get_by_index(i).getId() == p.getId())
        {
            produse.get_by_index(i) = p;
            found = true;
        }
    }

    if (!found)
    {
        throw RepositoryException("Nu exista produsul cu id-ul dat!");
    }
}

CustomVector<Produs>& RepoProduse::getAll()
{
    return this->produse;
}
