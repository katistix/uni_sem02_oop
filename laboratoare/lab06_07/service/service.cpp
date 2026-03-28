#include "service.h"

void ServiceProduse::adauga(const std::string& nume, const std::string& tip, double pret, const std::string& producator) {
    Produs p(nextId++, nume, tip, pret, producator);
    repo.adauga(p);
}

void ServiceProduse::sterge(const int id) {
    repo.sterge(id);
}

void ServiceProduse::modifica(const int id, const std::string& nume, const std::string& tip, double pret, const std::string& producator) {
    Produs p(id, nume, tip, pret, producator);
    repo.modifica(p);
}

std::vector<Produs> ServiceProduse::getAll() const {
    return repo.getAll();
}

std::vector<Produs> ServiceProduse::sortByFunction(bool (*cmp)(const Produs&, const Produs&)) const {
    std::vector<Produs> produse = repo.getAll();
    std::sort(produse.begin(), produse.end(), cmp);
    return produse;
}

std::vector<Produs> ServiceProduse::filterByFunction(bool (*fn)(const Produs&)) const {
    std::vector<Produs> produse = repo.getAll();
    std::vector<Produs> result;
    for (const Produs& p : produse)
        if (fn(p))
            result.push_back(p);
    return result;
}
