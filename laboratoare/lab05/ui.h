#ifndef UI_H
#define UI_H

/* ============================================================
 * Modul: ui.h
 * Descriere: Interfata utilizator consola (UI layer)
 * ============================================================ */

#include "service.h"

typedef struct {
    Service *service;
} UI;

/* Ciclu de viata */
UI  *ui_creeaza(Service *service);
void ui_distruge(UI *ui);

/* Pornire aplicatie */
void ui_ruleaza(UI *ui);

/* Meniuri interne (testate individual) */
void ui_meniu_principal(void);
void ui_meniu_vizualizare(void);
void ui_meniu_sortare(void);

/* Comenzi */
void ui_cmd_adauga(UI *ui);
void ui_cmd_modifica(UI *ui);
void ui_cmd_sterge(UI *ui);
void ui_cmd_vizualizeaza_toate(UI *ui);
void ui_cmd_filtreaza(UI *ui);
void ui_cmd_sorteaza(UI *ui);

/* Utilitare input cu validare */
int    ui_citeste_int(const char *prompt, int min, int max);
double ui_citeste_double(const char *prompt, double min);
void   ui_citeste_sir(const char *prompt, char *dest, int maxlen);

#endif /* UI_H */
