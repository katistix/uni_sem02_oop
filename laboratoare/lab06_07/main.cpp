#include <iostream>
#include "ui/ui.h"
#include "service/service.h"
#include "repo/repo.h"

using namespace std;

int main() {
    RepoProduse repo;
    ServiceProduse service(repo);
    UI ui(service);

    ui.run();
    
    return 0;
}