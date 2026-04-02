//
// Created by paultal on 01.04.2026.
//

#ifndef LAB06_07_V2_SERVICE_H
#define LAB06_07_V2_SERVICE_H

#include "../repo/repo.h"
#include "../domain/produs.h"

class ServiceProduse {
private:
    // pentru a genera id-uri unice,
    // in mod normal ar trebui sa fie in repo,
    // dar pentru simplitate il punem aici
    int nextId = 1;

    // injectam dependenta prin constructor
    RepoProduse& repo;
public:
    explicit ServiceProduse(RepoProduse& repo) : repo(repo) {}

    void adauga(const std::string& nume, const std::string& tip, double pret, const std::string& producator);
    void sterge(const int id) const;
    void modifica(const int id, const std::string& nume, const std::string& tip, double pret, const std::string& producator) const;
    std::vector<Produs> getAll() const;

    std::vector<Produs> sortByFunction(bool (*cmp)(const Produs&, const Produs&)) const;
    std::vector<Produs> filterByFunction(bool (*fn)(const Produs&)) const;
};

#endif //LAB06_07_V2_SERVICE_H