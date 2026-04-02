//
// Created by paultal on 01.04.2026.
//

#ifndef LAB06_07_V2_UTILS_H
#define LAB06_07_V2_UTILS_H


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


#endif //LAB06_07_V2_UTILS_H