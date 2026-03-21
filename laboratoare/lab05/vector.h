#ifndef VECTOR_H
#define VECTOR_H

/* ============================================================
 * Modul: vector.h
 * Descriere: Vector dinamic generic (layer infrastructura)
 * Stocheaza pointeri void*, cu optional destructor/copy callbacks
 * pentru managementul corect al memoriei.
 * ============================================================ */

#include <stddef.h>

#define CAPACITATE_INITIALA 4

typedef void (*VectorDestructor)(void *);

typedef struct {
    void             *date;
    int               lungime;
    int               capac;
    size_t            elem_size;
    VectorDestructor  destructor;
} Vector;

Vector *vector_creeaza(size_t elem_size, VectorDestructor destructor);
void    vector_distruge(Vector *v);

int  vector_adauga(Vector *v, const void *elem);
int  vector_sterge(Vector *v, int index);
int  vector_seteaza(Vector *v, int index, const void *elem);
void *vector_get(const Vector *v, int index);
int   vector_lungime(const Vector *v);

void *vector_copie(const Vector *v, void *(*copy_func)(const void *));

#endif /* VECTOR_H */
