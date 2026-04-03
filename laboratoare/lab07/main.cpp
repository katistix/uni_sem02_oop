#include <iostream>

#include "repo/RepoProduse.h"
#include "service/ServiceProduse.h"
#include "ui/UI.h"

using namespace std;

int main()
{
    // initializare
    RepoProduse repo;
    ProdusValidator validator;
    ServiceProduse srv(repo, validator);
    const UI ui(srv);

    ui.run();

    return 0;
}