#ifndef UTILS_H
#define UTILS_H

#include "../domain/produs.h"
#include <string>

// Comparatori pentru sortare
bool cmpByNume(const Produs& a, const Produs& b);
bool cmpByNumeDesc(const Produs& a, const Produs& b);
bool cmpByPret(const Produs& a, const Produs& b);
bool cmpByPretDesc(const Produs& a, const Produs& b);
bool cmpByNumeSiTip(const Produs& a, const Produs& b);

// Filtre — seteaza parametrul, apoi pasezi functia ca pointer
void setFilterPretMax(double pretMax);
bool filterByPretMax(const Produs& p);

void setFilterProducator(const std::string& producator);
bool filterByProducator(const Produs& p);

void setFilterTip(const std::string& tip);
bool filterByTip(const Produs& p);

#endif // UTILS_H
