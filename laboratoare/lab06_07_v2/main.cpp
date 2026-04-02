#include "ui/ui.h"
#include "service/service.h"
#include "repo/repo.h"

int main() {
    RepoProduse repo;
    ServiceProduse service(repo);
    const UI ui(service);

    ui.run();

    return 0;
}