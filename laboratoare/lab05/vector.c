#include <stdlib.h>
#include <string.h>
#include "vector.h"

/* ============================================================
 * Modul: vector.c – vector dinamic generic cu realocare
 * ============================================================ */

Vector *vector_creeaza(size_t elem_size, VectorDestructor destructor)
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    if (!v) return NULL;
    v->date = malloc(CAPACITATE_INITIALA * elem_size);
    if (!v->date) { free(v); return NULL; }
    v->lungime    = 0;
    v->capac      = CAPACITATE_INITIALA;
    v->elem_size  = elem_size;
    v->destructor = destructor;
    return v;
}

void vector_distruge(Vector *v)
{
    if (!v) return;
    if (v->destructor && v->date) {
        int i;
        char *p = (char *)v->date;
        for (i = 0; i < v->lungime; i++)
            v->destructor(p + i * v->elem_size);
    }
    free(v->date);
    free(v);
}

static int vector_creste(Vector *v)
{
    int nou_capac = v->capac * 2;
    void *nou = realloc(v->date, nou_capac * v->elem_size);
    if (!nou) return 0;
    v->date  = nou;
    v->capac = nou_capac;
    return 1;
}

int vector_adauga(Vector *v, const void* elem)
{
    if (!v) return 0;
    if (v->lungime == v->capac)
        if (!vector_creste(v)) return 0;
    memcpy((char *)v->date + v->lungime * v->elem_size, elem, v->elem_size);
    v->lungime++;
    return 1;
}

int vector_sterge(Vector *v, int index)
{
    if (!v || index < 0 || index >= v->lungime) return 0;
    if (index < v->lungime - 1) {
        char *p = (char *)v->date;
        memmove(p + index * v->elem_size,
                p + (index + 1) * v->elem_size,
                (v->lungime - index - 1) * v->elem_size);
    }
    v->lungime--;
    return 1;
}

int vector_seteaza(Vector *v, int index, const void *elem)
{
    if (!v || index < 0) return 0;
    while (v->capac <= index) {
        if (!vector_creste(v)) return 0;
    }
    while (v->lungime <= index) {
        v->lungime++;
    }
    memcpy((char *)v->date + index * v->elem_size, elem, v->elem_size);
    return 1;
}

void *vector_get(const Vector *v, int index)
{
    if (!v || index < 0 || index >= v->lungime) return NULL;
    return (char *)v->date + index * v->elem_size;
}

int vector_lungime(const Vector *v)
{
    if (!v) return 0;
    return v->lungime;
}

void *vector_copie(const Vector *v, void *(*copy_func)(const void *))
{
    if (!v || !copy_func) return NULL;
    Vector *c = vector_creeaza(v->elem_size, v->destructor);
    if (!c) return NULL;
    int i;
    for (i = 0; i < v->lungime; i++) {
        void *elem = (char *)v->date + i * v->elem_size;
        void *copied = copy_func(elem);
        if (!copied) { vector_distruge(c); return NULL; }
        memcpy((char *)c->date + c->lungime * c->elem_size, copied, c->elem_size);
        c->lungime++;
    }
    return c;
}
