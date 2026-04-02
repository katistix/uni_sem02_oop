//
// Created by paultal on 02.04.2026.
//

#include "Produs.h"
#include <cstring>


Produs::Produs(const int id, char *nume, char *tip, const double pret, char *producator)
    : id(id), pret(pret)
{
    this->nume = new char[strlen(nume) + 1];
    strcpy(this->nume, nume);
    this->tip = new char[strlen(tip) + 1];
    strcpy(this->tip, tip);
    this->producator = new char[strlen(producator) + 1];
    strcpy(this->producator, producator);
}

Produs::Produs(const Produs& other) : id(other.id), pret(other.pret)
{
    this->nume = new char[strlen(other.nume) + 1];
    strcpy(this->nume, other.nume);
    this->tip = new char[strlen(other.tip) + 1];
    strcpy(this->tip, other.tip);
    this->producator = new char[strlen(other.producator) + 1];
    strcpy(this->producator, other.producator);
}

Produs& Produs::operator=(const Produs& other)
{
    if (this == &other) return *this;
    delete[] this->nume;
    delete[] this->tip;
    delete[] this->producator;
    this->id = other.id;
    this->pret = other.pret;
    this->nume = new char[strlen(other.nume) + 1];
    strcpy(this->nume, other.nume);
    this->tip = new char[strlen(other.tip) + 1];
    strcpy(this->tip, other.tip);
    this->producator = new char[strlen(other.producator) + 1];
    strcpy(this->producator, other.producator);
    return *this;
}

Produs::~Produs()
{
    delete[] nume;
    delete[] tip;
    delete[] producator;
}

int Produs::getId() const {
    return id;
}

char *Produs::getNume() const {
    return nume;
}

char *Produs::getTip() const {
    return tip;
}

double Produs::getPret() const {
    return pret;
}

char *Produs::getProducator() const {
    return producator;
}
