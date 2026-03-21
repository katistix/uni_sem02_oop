#ifndef REPO_H
#define REPO_H

/* ============================================================
 * Modul: repo.h
 * Descriere: Strat acces date (repository layer)
 * ============================================================ */

#include "vector.h"
#include "tranzactie.h"

typedef struct {
    Vector *tranzactii;
    int     urmatorul_id;
} Repo;

/* Ciclu de viata */
Repo *repo_creeaza(void);
void  repo_distruge(Repo *r);

/* CRUD */
int   repo_adauga(Repo *r, Tranzactie t);
int   repo_sterge_dupa_id(Repo *r, int id);
int   repo_modifica(Repo *r, int id, int zi, double suma,
                    const char *tip, const char *descriere);

/* Cautare */
Tranzactie *repo_gaseste_dupa_id(const Repo *r, int id);
int         repo_index_dupa_id(const Repo *r, int id);

/* Acces lista */
Vector *repo_get_toate(const Repo *r);
int     repo_contor(const Repo *r);
int     repo_urmatorul_id(const Repo *r);

/// @brief Restaureaza starea repo-ului dintr-un vector de tranzactii 
/// @param r 
/// @param v 
void    repo_restore(Repo *r, Vector *v);

#endif /* REPO_H */
