#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

/* ============================================================
 * Modul: ui.c – interfata utilizator consola
 * ============================================================ */

UI *ui_creeaza(Service *service)
{
    UI *ui = (UI *)malloc(sizeof(UI));
    if (!ui) return NULL;
    ui->service = service;
    return ui;
}

void ui_distruge(UI *ui) { if (ui) free(ui); }

/* ============================================================
 * Utilitare input cu validare
 * ============================================================ */

int ui_citeste_int(const char *prompt, int min, int max)
{
    int val;
    char buf[64];
    while (1) {
        printf("%s [%d-%d]: ", prompt, min, max);
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        if (sscanf(buf, "%d", &val) == 1 && val >= min && val <= max)
            return val;
        printf("  !! Valoare invalida. Introduceti un intreg intre %d si %d.\n",
               min, max);
    }
}

double ui_citeste_double(const char *prompt, double min)
{
    double val;
    char buf[64];
    while (1) {
        printf("%s (> %.2f): ", prompt, min);
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        if (sscanf(buf, "%lf", &val) == 1 && val > min)
            return val;
        printf("  !! Valoare invalida. Suma trebuie sa fie > %.2f.\n", min);
    }
}

void ui_citeste_sir(const char *prompt, char *dest, int maxlen)
{
    while (1) {
        printf("%s: ", prompt);
        if (!fgets(dest, maxlen, stdin)) continue;
        /* Elimina newline */
        int len = (int)strlen(dest);
        if (len > 0 && dest[len - 1] == '\n') dest[len - 1] = '\0';
        if (strlen(dest) > 0) return;
        printf("  !! Campul nu poate fi gol.\n");
    }
}

static int citeste_tip(char *tip)
{
    printf("  Tip (1=intrare / 2=iesire): ");
    char buf[16];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    int opt;
    if (sscanf(buf, "%d", &opt) != 1) return 0;
    if (opt == 1) { strcpy(tip, "intrare"); return 1; }
    if (opt == 2) { strcpy(tip, "iesire");  return 1; }
    printf("  !! Optiune invalida.\n");
    return 0;
}

/* ============================================================
 * Meniuri
 * ============================================================ */

void ui_meniu_principal(void)
{
    printf("\nGESTIUNE CONT BANCAR\n");
    printf("  1. Adauga tranzactie\n");
    printf("  2. Modifica tranzactie\n");
    printf("  3. Sterge tranzactie\n");
    printf("  4. Vizualizeaza toate\n");
    printf("  5. Filtreaza tranzactii\n");
    printf("  6. Sorteaza tranzactii\n");
    printf("  7. Undo\n");
    printf("  0. Iesire\n");
    printf("  Alegere: ");
}

void ui_meniu_vizualizare(void)
{
    printf("\n  -- Filtrare --\n");
    printf("  1. Dupa tip (intrare/iesire)\n");
    printf("  2. Suma mai mare decat...\n");
    printf("  3. Suma mai mica decat...\n");
    printf("  Alegere: ");
}

void ui_meniu_sortare(void)
{
    printf("\n  -- Sortare --\n");
    printf("  1. Dupa suma crescator\n");
    printf("  2. Dupa suma descrescator\n");
    printf("  3. Dupa zi crescator\n");
    printf("  4. Dupa zi descrescator\n");
    printf("  Alegere: ");
}

/* ============================================================
 * Afisare lista
 * ============================================================ */
static void afiseaza_vector(const Vector *v, const char *titlu)
{
    printf("\n  -- %s --\n", titlu);
    int n = vector_lungime(v);
    if (n == 0) { printf("  (nicio tranzactie)\n"); return; }
    printf("  %-5s %-4s %-12s %-8s %s\n",
           "ID", "Zi", "Suma", "Tip", "Descriere");
    printf("  %s\n", "-------------------------------------------------");
    int i;
    for (i = 0; i < n; i++)
        tranzactie_afiseaza(vector_get(v, i));
    printf("  Total: %d tranzactii\n", n);
}

/* ============================================================
 * Comenzi
 * ============================================================ */

void ui_cmd_adauga(UI *ui)
{
    printf("\n  === Adauga tranzactie ===\n");
    int    zi   = ui_citeste_int("  Ziua", 1, 31);
    double suma = ui_citeste_double("  Suma", 0.0);
    char   tip[TIP_MAX];
    while (!citeste_tip(tip));
    char   desc[DESC_MAX];
    ui_citeste_sir("  Descriere", desc, DESC_MAX);

    int rez = service_adauga(ui->service, zi, suma, tip, desc);
    if (rez == 1)
        printf("  >> Tranzactie adaugata cu succes!\n");
    else
        printf("  !! Eroare la adaugare (cod %d).\n", rez);
}

void ui_cmd_modifica(UI *ui)
{
    printf("\n  === Modifica tranzactie ===\n");
    if (service_contor(ui->service) == 0) {
        printf("  (nicio tranzactie de modificat)\n"); return;
    }
    afiseaza_vector(service_get_toate(ui->service), "Tranzactii existente");

    int id = ui_citeste_int("  ID tranzactie de modificat", 1, 99999);
    printf("  Datele noi:\n");
    int    zi   = ui_citeste_int("  Ziua", 1, 31);
    double suma = ui_citeste_double("  Suma", 0.0);
    char   tip[TIP_MAX];
    while (!citeste_tip(tip));
    char   desc[DESC_MAX];
    ui_citeste_sir("  Descriere", desc, DESC_MAX);

    int rez = service_modifica(ui->service, id, zi, suma, tip, desc);
    if (rez == 1)
        printf("  >> Tranzactie modificata cu succes!\n");
    else if (rez == -3)
        printf("  !! ID-ul %d nu exista.\n", id);
    else
        printf("  !! Date invalide (cod %d).\n", rez);
}

void ui_cmd_sterge(UI *ui)
{
    printf("\n  === Sterge tranzactie ===\n");
    if (service_contor(ui->service) == 0) {
        printf("  (nicio tranzactie de sters)\n"); return;
    }
    afiseaza_vector(service_get_toate(ui->service), "Tranzactii existente");

    int id  = ui_citeste_int("  ID tranzactie de sters", 1, 99999);
    int rez = service_sterge(ui->service, id);
    if (rez == 1)
        printf("  >> Tranzactie stearsa cu succes!\n");
    else if (rez == -2)
        printf("  !! ID-ul %d nu exista.\n", id);
    else
        printf("  !! Eroare la stergere.\n");
}

void ui_cmd_vizualizeaza_toate(UI *ui)
{
    afiseaza_vector(service_get_toate(ui->service), "Toate tranzactiile");
}

void ui_cmd_filtreaza(UI *ui)
{
    ui_meniu_vizualizare();
    char buf[8];
    if (!fgets(buf, sizeof(buf), stdin)) return;
    int opt;
    if (sscanf(buf, "%d", &opt) != 1) return;

    Vector *rez = NULL;
    char titlu[64];

    if (opt == 1) {
        char tip[TIP_MAX];
        while (!citeste_tip(tip));
        rez = service_filtreaza(ui->service, pred_tip, tip);
        snprintf(titlu, sizeof(titlu), "Tranzactii de tip: %s", tip);
    } else if (opt == 2) {
        double prag = ui_citeste_double("  Prag suma", 0.0);
        rez = service_filtreaza(ui->service, pred_suma_mai_mare, &prag);
        snprintf(titlu, sizeof(titlu), "Suma > %.2f", prag);
    } else if (opt == 3) {
        double prag = ui_citeste_double("  Prag suma", 0.0);
        rez = service_filtreaza(ui->service, pred_suma_mai_mica, &prag);
        snprintf(titlu, sizeof(titlu), "Suma < %.2f", prag);
    } else {
        printf("  !! Optiune invalida.\n"); return;
    }
    if (rez) { afiseaza_vector(rez, titlu); vector_distruge(rez); }
}

void ui_cmd_sorteaza(UI *ui)
{
    ui_meniu_sortare();
    char buf[8];
    if (!fgets(buf, sizeof(buf), stdin)) return;
    int opt;
    if (sscanf(buf, "%d", &opt) != 1) return;

    Vector *rez  = NULL;
    const char *titlu = "";

    switch (opt) {
        case 1: rez = service_sorteaza(ui->service, cmp_suma_asc);
                titlu = "Sortate dupa suma crescator"; break;
        case 2: rez = service_sorteaza(ui->service, cmp_suma_desc);
                titlu = "Sortate dupa suma descrescator"; break;
        case 3: rez = service_sorteaza(ui->service, cmp_zi_asc);
                titlu = "Sortate dupa zi crescator"; break;
        case 4: rez = service_sorteaza(ui->service, cmp_zi_desc);
                titlu = "Sortate dupa zi descrescator"; break;
        default: printf("  !! Optiune invalida.\n"); return;
    }
    if (rez) { afiseaza_vector(rez, titlu); vector_distruge(rez); }
}

void ui_cmd_undo(UI *ui)
{
    int rez = service_undo(ui->service);
    if (rez == 1)
        printf("  >> Undo realizat cu succes!\n");
    else if (rez == -2)
        printf("  !! Nu exista operatii de undo.\n");
    else
        printf("  !! Eroare la undo.\n");
}

/* ============================================================
 * Bucla principala
 * ============================================================ */

void ui_ruleaza(UI *ui)
{
    int activ = 1;
    while (activ) {
        ui_meniu_principal();
        char buf[8];
        if (!fgets(buf, sizeof(buf), stdin)) continue;
        int opt;
        if (sscanf(buf, "%d", &opt) != 1) continue;

        switch (opt) {
            case 1: ui_cmd_adauga(ui);            break;
            case 2: ui_cmd_modifica(ui);          break;
            case 3: ui_cmd_sterge(ui);            break;
            case 4: ui_cmd_vizualizeaza_toate(ui);break;
            case 5: ui_cmd_filtreaza(ui);         break;
            case 6: ui_cmd_sorteaza(ui);          break;
            case 7: ui_cmd_undo(ui);              break;
            case 0: activ = 0;
                    printf("  La revedere!\n");   break;
            default:printf("  !! Optiune invalida.\n");
        }
    }
}