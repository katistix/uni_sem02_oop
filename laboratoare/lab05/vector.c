#include <stdlib.h>
#include <string.h>
#include "vector.h"

/* ============================================================
 * Modul: vector.c – vector dinamic cu realocare automata
 * ============================================================ */

Vector *vector_creeaza(void)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (!v) return NULL;
    v->date    = (Tranzactie *)malloc(CAPACITATE_INITIALA * sizeof(Tranzactie));
    if (!v->date) { free(v); return NULL; }
    v->lungime = 0;
    v->capac   = CAPACITATE_INITIALA;
    return v;
}

void vector_distruge(Vector *v)
{
    if (!v) return;
    free(v->date);
    free(v);
}

/* Dubleaza capacitatea daca e nevoie */
static int vector_creste(Vector *v)
{
    int      nou_capac = v->capac * 2;
    Tranzactie *nou   = (Tranzactie *)realloc(v->date,
                                               nou_capac * sizeof(Tranzactie));
    if (!nou) return 0;
    v->date  = nou;
    v->capac = nou_capac;
    return 1;
}

int vector_adauga(Vector *v, Tranzactie t)
{
    if (!v) return 0;
    if (v->lungime == v->capac)
        if (!vector_creste(v)) return 0;
    v->date[v->lungime++] = t;
    return 1;
}

int vector_sterge(Vector *v, int index)
{
    if (!v || index < 0 || index >= v->lungime) return 0;
    /* Muta elementele la stanga */
    int i;
    for (i = index; i < v->lungime - 1; i++)
        v->date[i] = v->date[i + 1];
    v->lungime--;
    return 1;
}

int vector_seteaza(Vector *v, int index, Tranzactie t)
{
    if (!v || index < 0 || index >= v->lungime) return 0;
    v->date[index] = t;
    return 1;
}

Tranzactie *vector_get(const Vector *v, int index)
{
    if (!v || index < 0 || index >= v->lungime) return NULL;
    return &v->date[index];
}

int vector_lungime(const Vector *v)
{
    if (!v) return 0;
    return v->lungime;
}

Vector *vector_copie(const Vector *v)
{
    if (!v) return NULL;
    Vector *c = vector_creeaza();
    if (!c) return NULL;
    int i;
    for (i = 0; i < v->lungime; i++)
        vector_adauga(c, v->date[i]);
    return c;
}
