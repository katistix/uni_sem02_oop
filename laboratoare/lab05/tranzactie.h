#ifndef TRANZACTIE_H
#define TRANZACTIE_H

/* ============================================================
 * Modul: tranzactie.h
 * Descriere: Definitia entitatii Tranzactie (layer domeniu)
 * ============================================================ */

#define DESC_MAX 128
#define TIP_MAX  16

typedef struct {
    int    id;
    int    zi;       /* 1-31 */
    double suma;
    char   tip[TIP_MAX];   /* "intrare" sau "iesire" */
    char   descriere[DESC_MAX];
} Tranzactie;

/* Constructori / getteri / setteri */
Tranzactie  tranzactie_creeaza(int id, int zi, double suma,
                               const char *tip, const char *descriere);

int         tranzactie_get_id(const Tranzactie *t);
int         tranzactie_get_zi(const Tranzactie *t);
double      tranzactie_get_suma(const Tranzactie *t);
const char *tranzactie_get_tip(const Tranzactie *t);
const char *tranzactie_get_descriere(const Tranzactie *t);

void        tranzactie_set_zi(Tranzactie *t, int zi);
void        tranzactie_set_suma(Tranzactie *t, double suma);
void        tranzactie_set_tip(Tranzactie *t, const char *tip);
void        tranzactie_set_descriere(Tranzactie *t, const char *descriere);

/* Afisare */
void        tranzactie_afiseaza(const Tranzactie *t);

/* Validare domeniu */
int         tranzactie_valid_zi(int zi);
int         tranzactie_valid_suma(double suma);
int         tranzactie_valid_tip(const char *tip);

#endif /* TRANZACTIE_H */
