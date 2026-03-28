#include "utils.h"

bool cmpByNume(const Produs& a, const Produs& b) {
    return a.getNume() < b.getNume();
}

bool cmpByNumeDesc(const Produs& a, const Produs& b) {
    return a.getNume() > b.getNume();
}

bool cmpByPret(const Produs& a, const Produs& b) {
    return a.getPret() < b.getPret();
}

bool cmpByPretDesc(const Produs& a, const Produs& b) {
    return a.getPret() > b.getPret();
}

bool cmpByNumeSiTip(const Produs& a, const Produs& b) {
    if (a.getNume() != b.getNume())
        return a.getNume() < b.getNume();
    return a.getTip() < b.getTip();
}

std::function<bool(const Produs&)> makeFilterByPretMax(double pretMax) {
    return [pretMax](const Produs& p) {
        return p.getPret() <= pretMax;
    };
}

std::function<bool(const Produs&)> makeFilterByProducator(const std::string& producator) {
    return [producator](const Produs& p) {
        return p.getProducator() == producator;
    };
}

std::function<bool(const Produs&)> makeFilterByTip(const std::string& tip) {
    return [tip](const Produs& p) {
        return p.getTip() == tip;
    };
}
