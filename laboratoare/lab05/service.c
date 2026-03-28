#include <stdlib.h>
#include <string.h>
#include "service.h"

/* ============================================================
 * Modul: service.c – logica de business
 * ============================================================ */

static void vector_ptr_destructor(void *p)
{
    vector_distruge(*(Vector **)p);
}

Service *service_creeaza(Repo *repo)
{
    Service *s = (Service *)malloc(sizeof(Service));
    if (!s) return NULL;
    s->repo = repo;
    s->history = vector_creeaza(sizeof(Vector *), vector_ptr_destructor);
    if (!s->history) { free(s); return NULL; }
    return s;
}

void service_distruge(Service *s)
{
    if (!s) return;
    vector_distruge(s->history);
    free(s);
}

static void *tranzactie_copy(const void *p)
{
    const Tranzactie *orig = (const Tranzactie *)p;
    Tranzactie *copy = (Tranzactie *)malloc(sizeof(Tranzactie));
    if (copy) *copy = *orig;
    return copy;
}

/* ---- Validare interna ---- */
static int valideaza(int zi, double suma, const char *tip)
{
    return tranzactie_valid_zi(zi)   &&
           tranzactie_valid_suma(suma) &&
           tranzactie_valid_tip(tip);
}

static int history_push(Vector *history, Vector *v)
{
    Vector **elem = (Vector **)malloc(sizeof(Vector *));
    if (!elem) return 0;
    *elem = v;
    vector_adauga(history, elem);
    free(elem);
    return 1;
}

int service_adauga(Service *s, int zi, double suma,
                   const char *tip, const char *descriere)
{
    if (!s) return -1;
    if (!valideaza(zi, suma, tip)) return -2;
    Vector *copie = vector_copie(repo_get_toate(s->repo), tranzactie_copy);
    if (!copie) return -4;
    if (!history_push(s->history, copie)) { vector_distruge(copie); return -4; }
    Tranzactie t = tranzactie_creeaza(0, zi, suma, tip, descriere);
    if (!repo_adauga(s->repo, t)) return -3;
    return 1;
}

int service_sterge(Service *s, int id)
{
    if (!s) return -1;
    if (!repo_gaseste_dupa_id(s->repo, id)) return -2;
    Vector *copie = vector_copie(repo_get_toate(s->repo), tranzactie_copy);
    if (!copie) return -4;
    if (!history_push(s->history, copie)) { vector_distruge(copie); return -4; }
    return repo_sterge_dupa_id(s->repo, id) ? 1 : -3;
}

int service_modifica(Service *s, int id, int zi, double suma,
                     const char *tip, const char *descriere)
{
    if (!s) return -1;
    if (!valideaza(zi, suma, tip)) return -2;
    if (!repo_gaseste_dupa_id(s->repo, id)) return -3;
    Vector *copie = vector_copie(repo_get_toate(s->repo), tranzactie_copy);
    if (!copie) return -5;
    if (!history_push(s->history, copie)) { vector_distruge(copie); return -5; }
    return repo_modifica(s->repo, id, zi, suma, tip, descriere) ? 1 : -4;
}

/* ---- Predicate filtrare ---- */
int pred_tip(const Tranzactie *t, const void *ctx)
{
    return strcmp(t->tip, (const char *)ctx) == 0;
}

int pred_suma_mai_mare(const Tranzactie *t, const void *ctx)
{
    return t->suma > *(const double *)ctx;
}

int pred_suma_mai_mica(const Tranzactie *t, const void *ctx)
{
    return t->suma < *(const double *)ctx;
}

/* ---- Filtrare generica ---- */
Vector *service_filtreaza(const Service *s, PredicatFn predicat, const void *ctx)
{
    Vector *rez = vector_creeaza(sizeof(Tranzactie), NULL);
    if (!s || !rez) return rez;
    Vector *toate = repo_get_toate(s->repo);
    int i, n = vector_lungime(toate);
    for (i = 0; i < n; i++) {
        Tranzactie *t = (Tranzactie *)vector_get(toate, i);
        if (predicat(t, ctx))
            vector_adauga(rez, t);
    }
    return rez;
}

/* ---- Comparatori sortare ---- */
int cmp_suma_asc(const void *a, const void *b)
{
    double da = ((const Tranzactie *)a)->suma;
    double db = ((const Tranzactie *)b)->suma;
    return (da > db) - (da < db);
}

int cmp_suma_desc(const void *a, const void *b) { return cmp_suma_asc(b, a); }

int cmp_zi_asc(const void *a, const void *b)
{
    return ((const Tranzactie *)a)->zi - ((const Tranzactie *)b)->zi;
}

int cmp_zi_desc(const void *a, const void *b) { return cmp_zi_asc(b, a); }

/* ---- Sortare generica (insertion sort cu comparator injectat) ---- */
Vector *service_sorteaza(const Service *s, ComparatorFn comparator)
{
    Vector *src = repo_get_toate(s->repo);
    Vector *rez = vector_creeaza(src->elem_size, NULL);
    if (!rez) return NULL;
    int i, j, n = vector_lungime(src);
    for (i = 0; i < n; i++) {
        Tranzactie cheie = *(Tranzactie *)vector_get(src, i);
        j = i - 1;
        while (j >= 0) {
            Tranzactie *prev = (Tranzactie *)vector_get(rez, j);
            if (!prev || comparator(prev, &cheie) <= 0) break;
            Tranzactie tmp = *prev;
            vector_seteaza(rez, j + 1, &tmp);
            j--;
        }
        vector_seteaza(rez, j + 1, &cheie);
    }
    return rez;
}

Vector *service_get_toate(const Service *s)
{ return repo_get_toate(s->repo); }

int service_contor(const Service *s)
{ return repo_contor(s->repo); }

int service_undo(Service *s)
{
    if (!s || !s->history) return -1;
    if (vector_lungime(s->history) == 0) return -2;
    Vector **last = (Vector **)vector_get(s->history, vector_lungime(s->history) - 1);
    if (!last || !*last) return -1;
    Vector *stare_anterioara = *last;
    s->history->lungime--;
    repo_restore(s->repo, stare_anterioara);
    return 1;
}
