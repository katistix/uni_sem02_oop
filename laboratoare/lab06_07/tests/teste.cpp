// #include "domain/produs.h"
#include "../domain/produs.h"
#include "../repo/repo.h"
#include "../service/service.h"
#include <iostream>
#include <cassert>


void test_domain_Produs() {
    Produs p(1, "Laptop", "Electronics", 1500.0, "Dell");

    assert(p.getId() == 1);
    assert(p.getNume() == "Laptop");
    assert(p.getTip() == "Electronics");
    assert(p.getPret() == 1500.0);
    assert(p.getProducator() == "Dell");
}

void test_repo_adauga() {
    RepoProduse repo;
    Produs p(1, "Laptop", "Electronics", 1500.0, "Dell");
    repo.adauga(p);
    assert(repo.getAll().size() == 1);
    assert(repo.getAll()[0].getId() == 1);
}

void test_repo_sterge() {
    RepoProduse repo;
    repo.adauga(Produs(1, "Laptop", "Electronics", 1500.0, "Dell"));
    repo.adauga(Produs(2, "Phone", "Electronics", 800.0, "Samsung"));
    repo.sterge(1);
    assert(repo.getAll().size() == 1);
    assert(repo.getAll()[0].getId() == 2);

    // sterge un id inexistent (nu crapa)
    repo.sterge(999);
    assert(repo.getAll().size() == 1);
}

void test_repo_modifica() {
    RepoProduse repo;
    repo.adauga(Produs(1, "Laptop", "Electronics", 1500.0, "Dell"));
    repo.modifica(Produs(1, "Laptop Pro", "Electronics", 2000.0, "Dell"));
    assert(repo.getAll()[0].getNume() == "Laptop Pro");
    assert(repo.getAll()[0].getPret() == 2000.0);

    // modifica un id inexistent (nu crapa)
    repo.modifica(Produs(999, "Ghost", "None", 0.0, "Nobody"));
    assert(repo.getAll().size() == 1);
}

void test_repo_getAll_empty() {
    RepoProduse repo;
    assert(repo.getAll().empty());
}


// service tests

void test_service_adauga() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("Laptop", "Electronics", 1500.0, "Dell");
    assert(service.getAll().size() == 1);
    assert(service.getAll()[0].getNume() == "Laptop");
}

void test_service_sterge() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("Laptop", "Electronics", 1500.0, "Dell");
    service.adauga("Phone", "Electronics", 800.0, "Samsung");
    service.sterge(1);
    assert(service.getAll().size() == 1);
    assert(service.getAll()[0].getId() == 2);

    // sterge un id inexistent (nu crapa)
    service.sterge(999);
    assert(service.getAll().size() == 1);
}

void test_service_modifica() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("Laptop", "Electronics", 1500.0, "Dell");
    service.modifica(1, "Laptop Pro", "Electronics", 2000.0, "Dell");
    assert(service.getAll()[0].getNume() == "Laptop Pro");
    assert(service.getAll()[0].getPret() == 2000.0);

    // modifica un id inexistent (nu crapa)
    service.modifica(999, "Ghost", "None", 0.0, "Nobody");
    assert(service.getAll().size() == 1);
}

void test_service_getAll_empty() {
    RepoProduse repo;
    ServiceProduse service(repo);
    assert(service.getAll().empty());
}



int main() {
    // Domain tests
    test_domain_Produs();

    // Repo tests
    test_repo_adauga();
    test_repo_sterge();
    test_repo_modifica();
    test_repo_getAll_empty();

    // Service tests
    test_service_adauga();
    test_service_sterge();
    test_service_modifica();
    test_service_getAll_empty();

    std::cout << "all good!" << std::endl;

    return 0;
}