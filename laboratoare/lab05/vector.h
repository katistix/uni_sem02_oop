#ifndef VECTOR_H
#define VECTOR_H

/* ============================================================
 * Modul: vector.h
 * Descriere: Vector dinamic generic (layer infrastructura)
 * Acomodeaza oricate elemente prin realocare dinamica.
 * ============================================================ */

#include "tranzactie.h"

#define CAPACITATE_INITIALA 4

typedef struct {
    Tranzactie *date;    /* pointer la zona alocata dinamic */
    int         lungime; /* nr elemente curente             */
    int         capac;   /* capacitate alocata              */
} Vector;

/* Ciclu de viata */
Vector *vector_creeaza(void);
void    vector_distruge(Vector *v);

/* Operatii */
int     vector_adauga(Vector *v, Tranzactie t);
int     vector_sterge(Vector *v, int index);
int     vector_seteaza(Vector *v, int index, Tranzactie t);
Tranzactie *vector_get(const Vector *v, int index);
int     vector_lungime(const Vector *v);

/* Utilitare */
Vector *vector_copie(const Vector *v);

#endif /* VECTOR_H */
