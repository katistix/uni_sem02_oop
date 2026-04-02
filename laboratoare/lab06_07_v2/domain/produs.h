//
// Created by paultal on 01.04.2026.
//

#ifndef LAB06_07_V2_PRODUS_H
#define LAB06_07_V2_PRODUS_H

#include <string>

class Produs {
private:
    int id;
    std::string nume;
    std::string tip;
    double pret;
    std::string producator;

    friend class RepoProduse; // pentru a permite repo-ului sa acceseze campurile private
public:
    // Constructor
    Produs(int id, const std::string& nume, const std::string& tip, double pret, const std::string& producator);

    // Copy constructor
    Produs(const Produs& other);

    // Getters
    int getId() const;
    std::string getNume() const;
    std::string getTip() const;
    double getPret() const;
    std::string getProducator() const;

    std::string toString() const {
        return "Produs{id=" + std::to_string(id) + ", nume='" + nume + "', tip='" + tip + "', pret=" + std::to_string(pret) + ", producator='" + producator + "'}";
    }
};

#endif //LAB06_07_V2_PRODUS_H