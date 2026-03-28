#include "utils.h"

bool cmpByNume(const Produs& a, const Produs& b) { return a.getNume() < b.getNume(); }

bool cmpByNumeDesc(const Produs& a, const Produs& b) { return a.getNume() > b.getNume(); }

bool cmpByPret(const Produs& a, const Produs& b) { return a.getPret() < b.getPret(); }

bool cmpByPretDesc(const Produs& a, const Produs& b) { return a.getPret() > b.getPret(); }

bool cmpByNumeSiTip(const Produs& a, const Produs& b) {
    if (a.getNume() != b.getNume())
        return a.getNume() < b.getNume();
    return a.getTip() < b.getTip();
}

static double g_pretMax;
static std::string g_producator;
static std::string g_tip;

void setFilterPretMax(double pretMax) { g_pretMax = pretMax; }
bool filterByPretMax(const Produs& p) { return p.getPret() <= g_pretMax; }

void setFilterProducator(const std::string& producator) { g_producator = producator; }
bool filterByProducator(const Produs& p) { return p.getProducator() == g_producator; }

void setFilterTip(const std::string& tip) { g_tip = tip; }
bool filterByTip(const Produs& p) { return p.getTip() == g_tip; }
