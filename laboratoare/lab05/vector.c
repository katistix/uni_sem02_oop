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

/* ============================================================
 * Vector de vectori (pentru history undo)
 * ============================================================ */

static int vv_creste(VectorVector *vv)
{
    int nou_capac = vv->capac * 2;
    Vector **nou = (Vector **)realloc(vv->elemente,
                                       nou_capac * sizeof(Vector *));
    if (!nou) return 0;
    vv->elemente = nou;
    vv->capac = nou_capac;
    return 1;
}

VectorVector *vv_creeaza(void)
{
    VectorVector *vv = (VectorVector *)malloc(sizeof(VectorVector));
    if (!vv) return NULL;
    vv->elemente = (Vector **)malloc(CAPACITATE_INITIALA * sizeof(Vector *));
    if (!vv->elemente) { free(vv); return NULL; }
    vv->lungime = 0;
    vv->capac = CAPACITATE_INITIALA;
    return vv;
}

void vv_distruge(VectorVector *vv)
{
    if (!vv) return;
    int i;
    for (i = 0; i < vv->lungime; i++)
        vector_distruge(vv->elemente[i]);
    free(vv->elemente);
    free(vv);
}

int vv_adauga(VectorVector *vv, Vector *v)
{
    if (!vv || !v) return 0;
    if (vv->lungime == vv->capac)
        if (!vv_creste(vv)) return 0;
    vv->elemente[vv->lungime++] = v;
    return 1;
}

Vector *vv_pop(VectorVector *vv)
{
    if (!vv || vv->lungime == 0) return NULL;
    return vv->elemente[--vv->lungime];
}

int vv_lungime(const VectorVector *vv)
{
    if (!vv) return 0;
    return vv->lungime;
}
