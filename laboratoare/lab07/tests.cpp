#include <cassert>
#include <iostream>

#include "domain/Produs.h"
#include "utils/CustomVector.h"

using namespace std;


// UTILS
void test_custom_vector_constructor()
{
    const CustomVector<int> myVector;
    assert(myVector.get_size() == 0);
}

// DOMAIN
void test_produs_constructor()
{
    const auto name = "nume1";
    const auto tip = "tip1";
    constexpr double pret = 3.14;
    const auto *producator = "producator1";
    const Produs produs(1, name, tip, pret, producator);

    assert(produs.getId() == 1);
    assert(produs.getNume() == name);
    assert(produs.getTip() == tip);
    assert(produs.getPret() == pret);
    assert(produs.getProducator() == producator);

}

int main()
{
    cout << "running tests...\n";

    test_custom_vector_constructor();

    cout << "all good!\n";
}