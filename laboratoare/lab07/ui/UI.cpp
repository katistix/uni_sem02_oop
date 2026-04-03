//
// Created by paultal on 02.04.2026.
//

#include "UI.h"
#include "../exceptions/RepositoryException.h"
#include "../validators/ProdusValidator.h"
#include <iostream>
#include <limits>

#include "../utils/ProdusComparators.h"

using std::cin;
using std::cout;

void UI::printMenu()
{
    cout << "Comenzi disponibile:\n";
    cout << "1. Adaugare produs\n";
    cout << "2. Afiseaza toate produsele\n";
    cout << "3. Sterge produs\n";
    cout << "4. Update produs\n";
    cout << "5. Sorteaza produse\n";
    cout << "6. Filtreaza produse\n";
    cout << "9. Incarca date dummy\n";
    cout << "0. Iesire\n";
    cout << ">>> ";

}

void UI::cmd_adauga() const
{
    cout << "ADAUGARE PRODUS:\n";

    int id;
    cout << "Introducere ID: ";
    if (!(cin >> id))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "ID invalid!\n";
        return;
    }

    char nume[100];
    cout << "Introducere nume: ";
    cin >> nume;

    char tip[100];
    cout << "Introducere tip: ";
    cin >> tip;

    double pret;
    cout << "Introducere pret: ";
    if (!(cin >> pret))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Pret invalid!\n";
        return;
    }

    char producator[100];
    cout << "Introducere producator: ";
    cin >> producator;

    try
    {
        this->srv.add(id, nume, tip, pret, producator);
        cout << "Produs adaugat cu succes!\n";
    }
    catch (const RepositoryException& e)
    {
        cout << "Eroare: " << e.message << "\n";
    }
    catch (const ValidationException& e)
    {
        cout << "Eroare validare: " << e.getMessage() << "\n";
    }
}

void UI::cmd_show_all() const
{
    CustomVector<Produs> &produse = this->srv.getAllProduse();

    for (int i=0;i<produse.get_size();i++)
    {
        cout << produse.get_by_index(i) << "\n";
    }
}

void UI::cmd_sterge() const
{
    cout << "ID-ul produsului de sters: ";
    int id;
    cin >> id;
    try
    {
        this->srv.sterge(id);
    }
    catch (const RepositoryException& e)
    {
       cout << "Eroare: " << e.message << "\n";
    }
}

void UI::cmd_update() const
{
    cout << "UPDATE PRODUS:\n";


    int id;
    cout << "Introducere ID: ";
    if (!(cin >> id))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "ID invalid!\n";
        return;
    }

    char nume[100];
    cout << "Introducere nume: ";
    cin >> nume;

    char tip[100];
    cout << "Introducere tip: ";
    cin >> tip;

    double pret;
    cout << "Introducere pret: ";
    if (!(cin >> pret))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Pret invalid!\n";
        return;
    }

    char producator[100];
    cout << "Introducere producator: ";
    cin >> producator;

    try
    {
        this->srv.update(id, nume, tip, pret, producator);
        cout << "Produs actualizat cu succes!\n";
    }
    catch (const RepositoryException& e)
    {
        cout << "Eroare: " << e.message << "\n";
    }
    catch (const ValidationException& e)
    {
        cout << "Eroare validare: " << e.getMessage() << "\n";
    }

}

void UI::cmd_sort() const
{
    cout << "SORTARE:\n";
    cout << "1. Sortare in functie de Pret\n";
    cout << "2. Sortare in functie de Nume\n";
    cout << "3. Sortare in functie de ID\n";
    cout << ">>> ";

    int option;
    cin >> option;

    CustomVector<Produs> sorted;
    switch (option)
    {
        case 1:
            sorted = this->srv.getSorted(&cmpByPret);
            break;
        case 2:
            sorted = this->srv.getSorted(&cmpByName);
            break;
        case 3:
            sorted = this->srv.getSorted(&cmpById);
            break;
        default:
            cout << "optiune invalida!\n";
            return;
    }

    for (int i = 0; i < sorted.get_size(); i++)
    {
        cout << sorted.get_by_index(i) << "\n";
    }
}

void UI::cmd_load_dummy() const
{
    this->srv.add(1, "Laptop", "Electronice", 3499.99, "Dell");
    this->srv.add(2, "Tricou", "Imbracaminte", 49.99, "Zara");
    this->srv.add(3, "Cafea", "Alimente", 29.99, "Lavazza");
    this->srv.add(4, "Telefon", "Electronice", 2999.99, "Samsung");
    this->srv.add(5, "Pantofi", "Imbracaminte", 199.99, "Nike");
    cout << "Date dummy incarcate cu succes!\n";
}

void UI::cmd_filter() const
{
    cout << "FILTRARE:\n";
    cout << "1. Filtrare dupa pret minim\n";
    cout << "2. Filtrare dupa tip\n";
    cout << ">>> ";

    int option;
    cin >> option;

    CustomVector<Produs> filtered;
    switch (option)
    {
        case 1:
        {
            double pretMin;
            cout << "Pret minim: ";
            if (!(cin >> pretMin))
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Pret invalid!\n";
                return;
            }
            filtered = this->srv.getFiltered([pretMin](const Produs& p) {
                return p.getPret() >= pretMin;
            });
            break;
        }
        case 2:
        {
            char tip[100];
            cout << "Tip: ";
            cin >> tip;
            filtered = this->srv.getFiltered([tip](const Produs& p) {
                return strcmp(p.getTip(), tip) == 0;
            });
            break;
        }
        default:
            cout << "optiune invalida!\n";
            return;
    }

    for (int i = 0; i < filtered.get_size(); i++)
    {
        cout << filtered.get_by_index(i) << "\n";
    }
}

void UI::run() const
{
    bool shouldExit = false;
    int cmd;
    while (!shouldExit)
    {
        printMenu();

        // read user inputs
        if (!(cin >> cmd))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "comanda invalida!\n";
            continue;
        }
        switch (cmd)
        {
        case 1:
            this->cmd_adauga();
            break;
        case 2:
            this->cmd_show_all();
            break;
        case 3:
            this->cmd_sterge();
            break;
        case 4:
            this->cmd_update();
            break;
        case 5:
            this->cmd_sort();
            break;
        case 6:
            this->cmd_filter();
            break;
        case 9:
            this->cmd_load_dummy();
            break;
        case 0:
            cout << "good bye!\n";
            shouldExit=true;
            break;
        default:
            cout << "comanda invalida!\n";
            break;
        }

        cin.ignore();

    }
}
