#include <stdlib.h>
#include <string.h>
#include "repo.h"

/* ============================================================
 * Modul: repo.c – strat acces date
 * ============================================================ */

Repo *repo_creeaza(void)
{
    Repo *r = (Repo *)malloc(sizeof(Repo));
    if (!r) return NULL;
    r->tranzactii  = vector_creeaza();
    r->urmatorul_id = 1;
    if (!r->tranzactii) { free(r); return NULL; }
    return r;
}

void repo_distruge(Repo *r)
{
    if (!r) return;
    vector_distruge(r->tranzactii);
    free(r);
}

int repo_adauga(Repo *r, Tranzactie t)
{
    if (!r) return 0;
    t.id = r->urmatorul_id;
    if (!vector_adauga(r->tranzactii, t)) return 0;
    r->urmatorul_id++;
    return 1;
}

int repo_index_dupa_id(const Repo *r, int id)
{
    if (!r) return -1;
    int i;
    for (i = 0; i < vector_lungime(r->tranzactii); i++) {
        Tranzactie *t = vector_get(r->tranzactii, i);
        if (t && t->id == id) return i;
    }
    return -1;
}

Tranzactie *repo_gaseste_dupa_id(const Repo *r, int id)
{
    int idx = repo_index_dupa_id(r, id);
    if (idx < 0) return NULL;
    return vector_get(r->tranzactii, idx);
}

int repo_sterge_dupa_id(Repo *r, int id)
{
    int idx = repo_index_dupa_id(r, id);
    if (idx < 0) return 0;
    return vector_sterge(r->tranzactii, idx);
}

int repo_modifica(Repo *r, int id, int zi, double suma,
                  const char *tip, const char *descriere)
{
    Tranzactie *t = repo_gaseste_dupa_id(r, id);
    if (!t) return 0;
    tranzactie_set_zi(t, zi);
    tranzactie_set_suma(t, suma);
    tranzactie_set_tip(t, tip);
    tranzactie_set_descriere(t, descriere);
    return 1;
}

Vector *repo_get_toate(const Repo *r)
{
    if (!r) return NULL;
    return r->tranzactii;
}

int repo_contor(const Repo *r)
{
    if (!r) return 0;
    return vector_lungime(r->tranzactii);
}

int repo_urmatorul_id(const Repo *r)
{
    if (!r) return -1;
    return r->urmatorul_id;
}
