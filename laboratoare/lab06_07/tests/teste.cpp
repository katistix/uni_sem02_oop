#include "../domain/produs.h"
#include "../repo/repo.h"
#include "../service/service.h"
#include "../service/utils.h"
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

// sort tests

void test_sort_byNume() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("Zebra", "A", 10.0, "X");
    service.adauga("Ana", "B", 20.0, "Y");
    service.adauga("Mara", "C", 15.0, "Z");

    auto rezultat = service.sortByFunction(cmpByNume);
    assert(rezultat[0].getNume() == "Ana");
    assert(rezultat[1].getNume() == "Mara");
    assert(rezultat[2].getNume() == "Zebra");
}

void test_sort_byNumeDesc() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("Ana", "A", 10.0, "X");
    service.adauga("Zebra", "B", 20.0, "Y");

    auto rezultat = service.sortByFunction(cmpByNumeDesc);
    assert(rezultat[0].getNume() == "Zebra");
    assert(rezultat[1].getNume() == "Ana");
}

void test_sort_byPret() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("A", "T", 300.0, "X");
    service.adauga("B", "T", 100.0, "X");
    service.adauga("C", "T", 200.0, "X");

    auto rezultat = service.sortByFunction(cmpByPret);
    assert(rezultat[0].getPret() == 100.0);
    assert(rezultat[1].getPret() == 200.0);
    assert(rezultat[2].getPret() == 300.0);
}

void test_sort_byPretDesc() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("A", "T", 100.0, "X");
    service.adauga("B", "T", 300.0, "X");

    auto rezultat = service.sortByFunction(cmpByPretDesc);
    assert(rezultat[0].getPret() == 300.0);
    assert(rezultat[1].getPret() == 100.0);
}

void test_sort_byNumeSiTip() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("Ana", "Zahar", 10.0, "X");
    service.adauga("Ana", "Aliment", 20.0, "Y");
    service.adauga("Bob", "Bautura", 15.0, "Z");

    auto rezultat = service.sortByFunction(cmpByNumeSiTip);
    // Ana/Aliment < Ana/Zahar < Bob/Bautura
    assert(rezultat[0].getNume() == "Ana" && rezultat[0].getTip() == "Aliment");
    assert(rezultat[1].getNume() == "Ana" && rezultat[1].getTip() == "Zahar");
    assert(rezultat[2].getNume() == "Bob");
}

// filter tests

void test_filter_byPretMax() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("A", "T", 100.0, "X");
    service.adauga("B", "T", 200.0, "X");
    service.adauga("C", "T", 300.0, "X");

    auto fn = makeFilterByPretMax(200.0);
    auto rezultat = service.filterByFunction(fn);
    assert(rezultat.size() == 2);
    assert(rezultat[0].getNume() == "A");
    assert(rezultat[1].getNume() == "B");
}

void test_filter_byProducator() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("A", "T", 100.0, "Dell");
    service.adauga("B", "T", 200.0, "Samsung");
    service.adauga("C", "T", 300.0, "Dell");

    auto fn = makeFilterByProducator("Dell");
    auto rezultat = service.filterByFunction(fn);
    assert(rezultat.size() == 2);
    assert(rezultat[0].getProducator() == "Dell");
    assert(rezultat[1].getProducator() == "Dell");
}

void test_filter_byTip() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("A", "Electronics", 100.0, "X");
    service.adauga("B", "Food", 200.0, "Y");
    service.adauga("C", "Electronics", 300.0, "Z");

    auto fn = makeFilterByTip("Electronics");
    auto rezultat = service.filterByFunction(fn);
    assert(rezultat.size() == 2);
    assert(rezultat[0].getTip() == "Electronics");
    assert(rezultat[1].getTip() == "Electronics");
}

void test_filter_empty_result() {
    RepoProduse repo;
    ServiceProduse service(repo);
    service.adauga("A", "T", 500.0, "X");

    auto fn = makeFilterByPretMax(100.0);
    auto rezultat = service.filterByFunction(fn);
    assert(rezultat.empty());
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

    // Sort tests
    test_sort_byNume();
    test_sort_byNumeDesc();
    test_sort_byPret();
    test_sort_byPretDesc();
    test_sort_byNumeSiTip();

    // Filter tests
    test_filter_byPretMax();
    test_filter_byProducator();
    test_filter_byTip();
    test_filter_empty_result();

    std::cout << "all good!" << std::endl;

    return 0;
}
