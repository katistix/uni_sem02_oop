#ifndef SERVICE_H
#define SERVICE_H

#include "../repo/repo.h"


class ServiceProduse {
private:
    // pentru a genera id-uri unice,
    // in mod normal ar trebui sa fie in repo,
    // dar pentru simplitate il punem aici
    int nextId = 1; 

    // injectam dependenta prin constructor
    RepoProduse& repo;
public:
    ServiceProduse(RepoProduse& repo) : repo(repo) {}

    void adauga(const std::string& nume, const std::string& tip, double pret, const std::string& producator);
    void sterge(const int id);
    void modifica(const int id, const std::string& nume, const std::string& tip, double pret, const std::string& producator);
    std::vector<Produs> getAll() const;
};

#endif // SERVICE_H