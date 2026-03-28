#include "ui.h"
#include "../service/utils.h"
#include <iostream>

void printMenu() {
    std::cout << "1. Adauga produs\n";
    std::cout << "2. Sterge produs\n";
    std::cout << "3. Modifica produs\n";
    std::cout << "4. Afiseaza produse\n";
    std::cout << "5. Sorteaza produse\n";
    std::cout << "6. Filtreaza produse\n";
    std::cout << "0. Iesire\n";
    std::cout << "Alege optiunea: ";
}

static void afiseazaProduse(const std::vector<Produs>& produse) {
    if (produse.empty()) {
        std::cout << "Nu exista produse!\n";
        return;
    }
    for (const auto& p : produse) {
        std::cout << p.toString() << "\n";
    }
}

static void uiSorteaza(ServiceProduse& service) {
    std::cout << "1. Dupa nume (crescator)\n";
    std::cout << "2. Dupa nume (descrescator)\n";
    std::cout << "3. Dupa pret (crescator)\n";
    std::cout << "4. Dupa pret (descrescator)\n";
    std::cout << "5. Dupa nume si tip\n";
    std::cout << "Alege criteriul: ";
    int opt;
    std::cin >> opt;
    std::vector<Produs> rezultat;
    if (opt == 1)
        rezultat = service.sortByFunction(cmpByNume);
    else if (opt == 2)
        rezultat = service.sortByFunction(cmpByNumeDesc);
    else if (opt == 3)
        rezultat = service.sortByFunction(cmpByPret);
    else if (opt == 4)
        rezultat = service.sortByFunction(cmpByPretDesc);
    else if (opt == 5)
        rezultat = service.sortByFunction(cmpByNumeSiTip);
    else {
        std::cout << "Optiune invalida!\n";
        return;
    }
    afiseazaProduse(rezultat);
}

static void uiFiltreaza(ServiceProduse& service) {
    std::cout << "1. Dupa pret maxim\n";
    std::cout << "2. Dupa producator\n";
    std::cout << "3. Dupa tip\n";
    std::cout << "Alege criteriul: ";
    int opt;
    std::cin >> opt;
    std::vector<Produs> rezultat;
    if (opt == 1) {
        double pretMax;
        std::cout << "Pret maxim: ";
        std::cin >> pretMax;
        setFilterPretMax(pretMax);
        rezultat = service.filterByFunction(filterByPretMax);
    } else if (opt == 2) {
        std::string producator;
        std::cout << "Producator: ";
        std::cin >> producator;
        setFilterProducator(producator);
        rezultat = service.filterByFunction(filterByProducator);
    } else if (opt == 3) {
        std::string tip;
        std::cout << "Tip: ";
        std::cin >> tip;
        setFilterTip(tip);
        rezultat = service.filterByFunction(filterByTip);
    } else {
        std::cout << "Optiune invalida!\n";
        return;
    }
    afiseazaProduse(rezultat);
}

void UI::run() {
    while (true) {
        printMenu();
        int opt;
        std::cin >> opt;

        if (opt == 0) {
            break;
        }

        try {
            if (opt == 1) {
                std::string nume, tip, producator;
                double pret;
                std::cout << "Nume: ";
                std::cin >> nume;
                std::cout << "Tip: ";
                std::cin >> tip;
                std::cout << "Pret: ";
                std::cin >> pret;
                std::cout << "Producator: ";
                std::cin >> producator;
                service.adauga(nume, tip, pret, producator);
            } else if (opt == 2) {
                int id;
                std::cout << "ID: ";
                std::cin >> id;
                service.sterge(id);
            } else if (opt == 3) {
                int id;
                std::string nume, tip, producator;
                double pret;
                std::cout << "ID: ";
                std::cin >> id;
                std::cout << "Nume: ";
                std::cin >> nume;
                std::cout << "Tip: ";
                std::cin >> tip;
                std::cout << "Pret: ";
                std::cin >> pret;
                std::cout << "Producator: ";
                std::cin >> producator;
                service.modifica(id, nume, tip, pret, producator);
            } else if (opt == 4) {
                afiseazaProduse(service.getAll());
            } else if (opt == 5) {
                uiSorteaza(service);
            } else if (opt == 6) {
                uiFiltreaza(service);
            } else {
                std::cout << "Optiune invalida!\n";
            }

            std::cout << "Apasa Enter pentru a continua...\n";
            std::cin.ignore();
            std::cin.get();
        }
        catch (const std::exception& ex) {
            std::cout << "Eroare: " << ex.what() << "\n";
        }
    }
}
