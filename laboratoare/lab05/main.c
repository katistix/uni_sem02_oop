#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
// #include <crtdbg.h>

#include <stdio.h>
#include "repo.h"
#include "service.h"
#include "ui.h"

/* Declaram functia de teste (implementata in test_all.c) */
void run_all_tests(void);

/* ============================================================
 * main.c – punct de intrare aplicatie
 * Arhitectura stratificata:
 * UI -> Service -> Repo -> Vector -> Tranzactie
 * ============================================================ */

int main(void)
{
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    // _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    /* 1. Rulam toate testele inainte de a porni aplicatia efectiv */
    run_all_tests();

    /* 2. Construieste straturile (dependency injection) */
    Repo    *repo    = repo_creeaza();
    Service *service = service_creeaza(repo);
    UI      *ui      = ui_creeaza(service);

    if (!repo || !service || !ui) {
        fprintf(stderr, "Eroare: memorie insuficienta la pornire.\n");
        /* Ne asiguram ca distrugerile accepta NULL in siguranta */
        ui_distruge(ui);
        service_distruge(service);
        repo_distruge(repo);
        return 1;
    }

    /* 3. Pornim interfata utilizator */
    ui_ruleaza(ui);

    /* 4. Eliberare resurse (ordine inversa constructiei) */
    ui_distruge(ui);
    service_distruge(service);
    repo_distruge(repo);

    // _CrtDumpMemoryLeaks();
    return 0;
}