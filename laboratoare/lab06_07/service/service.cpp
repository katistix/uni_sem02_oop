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

