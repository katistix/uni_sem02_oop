//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_PRODUS_H
#define LAB07_PRODUS_H
#include <ostream>


class Produs
{
private:
    int id;
    char *nume;
    char *tip;
    double pret;
    char *producator;
public:
    Produs() : id(0), nume(nullptr), tip(nullptr), pret(0), producator(nullptr) {}

    Produs(int id, const char *nume, const char *tip, double pret, const char *producator);

    Produs(const Produs& other);
    Produs& operator=(const Produs& other);
    ~Produs();

    // Getters
    int getId() const;
    char *getNume() const;
    char *getTip() const;
    double getPret() const;
    char *getProducator() const;

    friend std::ostream& operator<<(std::ostream& os, const Produs& p)
    {
        os << "Produs{id=" << p.id << ", nume=" << p.nume << ", tip=" << p.tip
           << ", pret=" << p.pret << ", producator=" << p.producator << "}";
        return os;
    }

};


#endif //LAB07_PRODUS_H