#include "produs.h"

#include <iostream>


// Constructor
Produs::Produs(const int id, const std::string& nume, const std::string& tip, const double pret, const std::string& producator)
    : id(id), nume(nume), tip(tip), pret(pret), producator(producator) {}


// Copy constructor
Produs::Produs(const Produs& other)
    : id(other.id), nume(other.nume), tip(other.tip), pret(other.pret), producator(other.producator)
{
    std::cout <<"copy constructor\n";
}


// implementarea getter-elor
int Produs::getId() const {
    return id;
}

std::string Produs::getNume() const {
    return nume;
}

std::string Produs::getTip() const {
    return tip;
}

double Produs::getPret() const {
    return pret;
}

std::string Produs::getProducator() const {
    return producator;
}