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
    char *name = "nume1";
    char *tip = "tip1";
    double pret = 3.14;
    char *producator = "producator1";
    Produs produs(1, name, tip, pret, producator);

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