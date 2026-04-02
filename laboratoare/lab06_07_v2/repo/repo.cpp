#include "repo.h"

void RepoProduse::adauga(const Produs& p) {
    produse.push_back(p);
}

void RepoProduse::sterge(const int id) {
    // cauta produsul cu id-ul dat si sterge-l din vector
    for (auto it = produse.begin(); it != produse.end(); ++it) {
        if (it->getId() == id) {
            produse.erase(it); // sterge produsul din vector
            break;
        }
    }
}

void RepoProduse::modifica(const Produs& produsNou) {
    // cauta produsul cu id-ul dat si modifica-l
    for (auto& p : produse) {
        if (p.getId() == produsNou.getId()) {
            p = produsNou;
            break;
        }
    }
}

std::vector<Produs> RepoProduse::getAll() const {
    return produse;
}