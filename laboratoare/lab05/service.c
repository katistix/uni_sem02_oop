#include <stdlib.h>
#include <string.h>
#include "service.h"

/* ============================================================
 * Modul: service.c – logica de business
 * ============================================================ */

Service *service_creeaza(Repo *repo)
{
    Service *s = (Service *)malloc(sizeof(Service));
    if (!s) return NULL;
    s->repo = repo;
    s->history = vv_creeaza();
    if (!s->history) { free(s); return NULL; }
    return s;
}

void service_distruge(Service *s)
{
    if (!s) return;
    vv_distruge(s->history);
    free(s);
}

/* ---- Validare interna ---- */
static int valideaza(int zi, double suma, const char *tip)
{
    return tranzactie_valid_zi(zi)   &&
           tranzactie_valid_suma(suma) &&
           tranzactie_valid_tip(tip);
}

int service_adauga(Service *s, int zi, double suma,
                   const char *tip, const char *descriere)
{
    if (!s) return -1;
    if (!valideaza(zi, suma, tip)) return -2;
    Vector *copie = vector_copie(repo_get_toate(s->repo));
    if (!copie) return -4;
    vv_adauga(s->history, copie);
    Tranzactie t = tranzactie_creeaza(0, zi, suma, tip, descriere);
    if (!repo_adauga(s->repo, t)) return -3;
    return 1;
}

int service_sterge(Service *s, int id)
{
    if (!s) return -1;
    if (!repo_gaseste_dupa_id(s->repo, id)) return -2;
    Vector *copie = vector_copie(repo_get_toate(s->repo));
    if (!copie) return -4;
    vv_adauga(s->history, copie);
    return repo_sterge_dupa_id(s->repo, id) ? 1 : -3;
}

int service_modifica(Service *s, int id, int zi, double suma,
                     const char *tip, const char *descriere)
{
    if (!s) return -1;
    if (!valideaza(zi, suma, tip)) return -2;
    if (!repo_gaseste_dupa_id(s->repo, id)) return -3;
    Vector *copie = vector_copie(repo_get_toate(s->repo));
    if (!copie) return -5;
    vv_adauga(s->history, copie);
    return repo_modifica(s->repo, id, zi, suma, tip, descriere) ? 1 : -4;
}

/* ---- Filtrare ---- */
Vector *service_filtreaza_tip(const Service *s, const char *tip)
{
    Vector *rez = vector_creeaza();
    if (!s || !rez) return rez;
    Vector *toate = repo_get_toate(s->repo);
    int i, n = vector_lungime(toate);
    for (i = 0; i < n; i++) {
        Tranzactie *t = vector_get(toate, i);
        if (strcmp(t->tip, tip) == 0)
            vector_adauga(rez, *t);
    }
    return rez;
}

Vector *service_filtreaza_suma_mai_mare(const Service *s, double prag)
{
    Vector *rez = vector_creeaza();
    if (!s || !rez) return rez;
    Vector *toate = repo_get_toate(s->repo);
    int i, n = vector_lungime(toate);
    for (i = 0; i < n; i++) {
        Tranzactie *t = vector_get(toate, i);
        if (t->suma > prag) vector_adauga(rez, *t);
    }
    return rez;
}

Vector *service_filtreaza_suma_mai_mica(const Service *s, double prag)
{
    Vector *rez = vector_creeaza();
    if (!s || !rez) return rez;
    Vector *toate = repo_get_toate(s->repo);
    int i, n = vector_lungime(toate);
    for (i = 0; i < n; i++) {
        Tranzactie *t = vector_get(toate, i);
        if (t->suma < prag) vector_adauga(rez, *t);
    }
    return rez;
}

/* ---- Sortare (insertion sort) ---- */
static Vector *sorteaza(const Service *s,
                        int (*cmp)(const Tranzactie *, const Tranzactie *))
{
    Vector *rez = vector_copie(repo_get_toate(s->repo));
    if (!rez) return NULL;
    int i, j, n = vector_lungime(rez);
    for (i = 1; i < n; i++) {
        Tranzactie cheie = *vector_get(rez, i);
        j = i - 1;
        while (j >= 0 && cmp(vector_get(rez, j), &cheie) > 0) {
            vector_seteaza(rez, j + 1, *vector_get(rez, j));
            j--;
        }
        vector_seteaza(rez, j + 1, cheie);
    }
    return rez;
}

static int cmp_suma_asc(const Tranzactie *a, const Tranzactie *b)
{ return (a->suma > b->suma) - (a->suma < b->suma); }

static int cmp_suma_desc(const Tranzactie *a, const Tranzactie *b)
{ return (a->suma < b->suma) - (a->suma > b->suma); }

static int cmp_zi_asc(const Tranzactie *a, const Tranzactie *b)
{ return a->zi - b->zi; }

static int cmp_zi_desc(const Tranzactie *a, const Tranzactie *b)
{ return b->zi - a->zi; }

Vector *service_sorteaza_suma_asc(const Service *s)  { return sorteaza(s, cmp_suma_asc);  }
Vector *service_sorteaza_suma_desc(const Service *s) { return sorteaza(s, cmp_suma_desc); }
Vector *service_sorteaza_zi_asc(const Service *s)    { return sorteaza(s, cmp_zi_asc);    }
Vector *service_sorteaza_zi_desc(const Service *s)   { return sorteaza(s, cmp_zi_desc);   }

Vector *service_get_toate(const Service *s)
{ return repo_get_toate(s->repo); }

int service_contor(const Service *s)
{ return repo_contor(s->repo); }


int service_undo(Service *s)
{
    if (!s || !s->history) return -1;
    if (vv_lungime(s->history) == 0) return -2;
    Vector *stare_anterioara = vv_pop(s->history);
    if (!stare_anterioara) return -1;
    repo_restore(s->repo, stare_anterioara);
    return 1;
}