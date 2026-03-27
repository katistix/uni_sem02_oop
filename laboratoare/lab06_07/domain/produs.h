#ifndef PRODUS_H
#define PRODUS_H

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


#endif // PRODUS_H