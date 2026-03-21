#ifndef SERVICE_H
#define SERVICE_H

/* ============================================================
 * Modul: service.h
 * Descriere: Strat logica de business (service layer)
 * ============================================================ */

#include "repo.h"
#include "vector.h"

typedef struct {
    Repo        *repo;
    VectorVector *history;
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

/* Filtrare - returneaza Vector nou (caller face free) */
Vector *service_filtreaza_tip(const Service *s, const char *tip);
Vector *service_filtreaza_suma_mai_mare(const Service *s, double prag);
Vector *service_filtreaza_suma_mai_mica(const Service *s, double prag);

/* Sortare - returneaza Vector nou (caller face free) */
Vector *service_sorteaza_suma_asc(const Service *s);
Vector *service_sorteaza_suma_desc(const Service *s);
Vector *service_sorteaza_zi_asc(const Service *s);
Vector *service_sorteaza_zi_desc(const Service *s);

/* Acces */
Vector *service_get_toate(const Service *s);
int     service_contor(const Service *s);


/* Undo */
int service_undo(Service *s);


#endif /* SERVICE_H */
