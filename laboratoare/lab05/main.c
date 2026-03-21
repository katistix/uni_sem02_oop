#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
// #include <crtdbg.h>

#include <stdio.h>
#include "repo.h"
#include "service.h"
#include "ui.h"

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

    /* 1. Construieste straturile (dependency injection) */
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

    /* 2. Pornim interfata utilizator */
    ui_ruleaza(ui);

    /* 3. Eliberare resurse (ordine inversa constructiei) */
    ui_distruge(ui);
    service_distruge(service);
    repo_distruge(repo);

    // _CrtDumpMemoryLeaks();
    return 0;
}