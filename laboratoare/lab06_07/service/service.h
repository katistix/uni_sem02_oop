#ifndef SERVICE_H
#define SERVICE_H

#include "../repo/repo.h"
#include <algorithm>

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

    template<typename Compare>
    std::vector<Produs> sortByFunction(Compare cmp) const {
        std::vector<Produs> produse = repo.getAll();
        std::sort(produse.begin(), produse.end(), cmp);
        return produse;
    }

    template<typename Predicate>
    std::vector<Produs> filterByFunction(Predicate fn) const {
        std::vector<Produs> produse = repo.getAll();
        std::vector<Produs> result;
        for (const auto& p : produse) {
            if (fn(p))
                result.push_back(p);
        }
        return result;
    }
};

#endif // SERVICE_H
