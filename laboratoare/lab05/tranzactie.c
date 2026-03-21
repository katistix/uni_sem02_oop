#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "tranzactie.h"

/* ============================================================
 * Modul: tranzactie.c – implementare entitate Tranzactie
 * ============================================================ */

Tranzactie tranzactie_creeaza(int id, int zi, double suma,
                               const char *tip, const char *descriere)
{
    Tranzactie t;
    t.id   = id;
    t.zi   = zi;
    t.suma = suma;
    strncpy(t.tip, tip, TIP_MAX - 1);
    strncpy(t.descriere, descriere, DESC_MAX - 1);
    t.tip[TIP_MAX - 1]         = '\0';
    t.descriere[DESC_MAX - 1]  = '\0';
    return t;
}

int    tranzactie_get_id(const Tranzactie *t)         { return t->id; }
int    tranzactie_get_zi(const Tranzactie *t)         { return t->zi; }
double tranzactie_get_suma(const Tranzactie *t)       { return t->suma; }
const char *tranzactie_get_tip(const Tranzactie *t)   { return t->tip; }
const char *tranzactie_get_descriere(const Tranzactie *t) { return t->descriere; }

void tranzactie_set_zi(Tranzactie *t, int zi)              { t->zi = zi; }
void tranzactie_set_suma(Tranzactie *t, double suma)       { t->suma = suma; }
void tranzactie_set_tip(Tranzactie *t, const char *tip)
{
    strncpy(t->tip, tip, TIP_MAX - 1);
    t->tip[TIP_MAX - 1] = '\0';
}
void tranzactie_set_descriere(Tranzactie *t, const char *descriere)
{
    strncpy(t->descriere, descriere, DESC_MAX - 1);
    t->descriere[DESC_MAX - 1] = '\0';
}

void tranzactie_afiseaza(const Tranzactie *t)
{
    printf("  [ID:%3d] Zi:%2d | Suma:%10.2f | Tip:%-8s | %s\n",
           t->id, t->zi, t->suma, t->tip, t->descriere);
}

int tranzactie_valid_zi(int zi)       { return zi >= 1 && zi <= 31; }
int tranzactie_valid_suma(double suma){ return suma > 0.0; }
int tranzactie_valid_tip(const char *tip)
{
    return strcmp(tip, "intrare") == 0 || strcmp(tip, "iesire") == 0;
}
