//
// Created by paultal on 03/04/2026.
//

#ifndef LAB07_PRODUSCOMPARATORS_H
#define LAB07_PRODUSCOMPARATORS_H

#include "../domain/Produs.h"


inline bool cmpByPret(const Produs& a, const Produs& b)
{
    return a.getPret() < b.getPret();
}

inline bool cmpById(const Produs& a, const Produs& b)
{
    return a.getId() < b.getId();
}

inline bool cmpByName(const Produs& a, const Produs& b)
{
    return strcmp(a.getNume(), b.getNume()) < 0;
}

#endif //LAB07_PRODUSCOMPARATORS_H
