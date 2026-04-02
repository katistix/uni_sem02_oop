//
// Created by paultal on 02.04.2026.
//

#include "UI.h"
#include "../exceptions/RepositoryException.h"
#include "../validators/ProdusValidator.h"
#include <iostream>
#include <limits>

using std::cin;
using std::cout;

void UI::printMenu()
{
    cout << "Comenzi disponibile:\n";
    cout << "1. Adaugare produs\n";
    cout << "2. Afiseaza toate produsele\n";
    cout << "3. Sterge produs\n";
    cout << "0. Iesire\n";
    cout << ">>> ";

}

void UI::cmd_adauga()
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

void UI::cmd_show_all()
{
    CustomVector<Produs> &produse = this->srv.getAllProduse();

    for (int i=0;i<produse.get_size();i++)
    {
        cout << *produse.get_by_index(i) << "\n";
    }
}

void UI::cmd_sterge()
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

void UI::run()
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
