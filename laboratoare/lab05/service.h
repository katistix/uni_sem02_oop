#ifndef SERVICE_H
#define SERVICE_H

/* ============================================================
 * Modul: service.h
 * Descriere: Strat logica de business (service layer)
 * ============================================================ */

#include "repo.h"
#include "vector.h"

typedef struct {
    Repo   *repo;
    Vector *history;
} Service;

/* Ciclu de viata */

Service *service_creeaza(Repo *repo);
void     service_distruge(Service *s);

/* Operatii principale */
int service_adauga(Service *s, int zi, double suma,
                   const char *tip, const char *descriere);
int service_sterge(Service *s, int id);
int service_modifica(Service *s, int id, int zi, double suma,
                     const char *tip, const char *descriere);

/* Tipuri pentru injectare comportament */
typedef int (*ComparatorFn)(const void *, const void *);
typedef int (*PredicatFn)(const Tranzactie *, const void *);

/* Sortare generica - returneaza Vector nou (caller face free) */
Vector *service_sorteaza(const Service *s, ComparatorFn comparator);

/* Comparatori predefiniti */
int cmp_suma_asc (const void *a, const void *b);
int cmp_suma_desc(const void *a, const void *b);
int cmp_zi_asc  (const void *a, const void *b);
int cmp_zi_desc (const void *a, const void *b);

/* Filtrare generica - returneaza Vector nou (caller face free) */
Vector *service_filtreaza(const Service *s, PredicatFn predicat, const void *ctx);

/* Predicate predefinite */
int pred_tip          (const Tranzactie *t, const void *ctx); /* ctx = char*   */
int pred_suma_mai_mare(const Tranzactie *t, const void *ctx); /* ctx = double* */
int pred_suma_mai_mica(const Tranzactie *t, const void *ctx); /* ctx = double* */

/* Acces */
Vector *service_get_toate(const Service *s);
int     service_contor(const Service *s);


/* Undo */
int service_undo(Service *s);


#endif /* SERVICE_H */
