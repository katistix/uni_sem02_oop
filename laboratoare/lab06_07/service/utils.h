#ifndef UTILS_H
#define UTILS_H

#include "../domain/produs.h"
#include <functional>
#include <string>

// Criterii de sortare — functii simple de comparatie
bool cmpByNume(const Produs& a, const Produs& b);
bool cmpByNumeDesc(const Produs& a, const Produs& b);
bool cmpByPret(const Produs& a, const Produs& b);
bool cmpByPretDesc(const Produs& a, const Produs& b);
bool cmpByNumeSiTip(const Produs& a, const Produs& b);

// Fabrici de filtre — returneaza un predicat cu parametrii capturati
std::function<bool(const Produs&)> makeFilterByPretMax(double pretMax);
std::function<bool(const Produs&)> makeFilterByProducator(const std::string& producator);
std::function<bool(const Produs&)> makeFilterByTip(const std::string& tip);

#endif // UTILS_H
