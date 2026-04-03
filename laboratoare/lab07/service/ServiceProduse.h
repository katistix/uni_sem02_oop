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

    void add(int id, const char *nume, const char *tip, double pret, const char *producator) const;
    void sterge(int id) const;
    void update(int id, char* name, char* tip, double pret, char* producator) const;
    [[nodiscard]] CustomVector<Produs>& getAllProduse() const;

    CustomVector<Produs> getSorted(const std::function<bool(const Produs&, const Produs&)>& cmp) const;
    CustomVector<Produs> getFiltered(const std::function<bool(const Produs&)>& predicate) const;

};


#endif //LAB07_SERVICEPRODUSE_H