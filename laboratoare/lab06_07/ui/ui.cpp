#include "ui.h"
#include <iostream>

void printMenu() {
    std::cout << "1. Adauga produs\n";
    std::cout << "2. Sterge produs\n";
    std::cout << "3. Modifica produs\n";
    std::cout << "4. Afiseaza produse\n";
    std::cout << "0. Iesire\n";
    std::cout << "Alege optiunea: ";
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
                auto produse = service.getAll();
                if (produse.empty()) {
                    std::cout << "Nu exista produse!\n";
                }
                for (const auto& p : produse) {
                    std::cout << p.toString() << "\n";
                    // std::cout << p.getId() << ": " << p.getNume() << ", " 
                    //           << p.getTip() << ", " << p.getPret() 
                    //           << ", " << p.getProducator() << "\n";
                }
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