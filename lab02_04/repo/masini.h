#ifndef MASINI_H
#define MASINI_H

#include "../domain/masina.h"

#define INITIAL_CAPACITY 10
#define CAPACITY_RESIZE_FACTOR 2

typedef struct {
  Masina *masini;
  int capacity; // capacitatea colectiei
  int count;    // cate masini sunt in colectie
} ColectieMasini;

// "constructor"
/// @brief Initializeaza colectia de masini cu o capacitate initiala si aloca memorie pentru array-ul de masini
/// @param colectie - pointer la colectia de masini care va fi initializata
void initialize_colectie(ColectieMasini *colectie);



/// @brief Adauga o masina in colectia de masini
/// @param colectie - pointer la colectia de masini in care va fi adaugata masina
/// @param masina_noua - masina care va fi adaugata
void add(ColectieMasini *colectie, Masina masina_noua);

/// @brief Cauta o masina dupa numarul matricol
/// @param colectie 
/// @param nr_matricol 
/// @param rezultat - pointer unde se va copia masina gasita
/// @return 1 daca masina a fost gasita, 0 altfel
int get_masina_by_nr_matricol(ColectieMasini *colectie, char *nr_matricol, Masina *rezultat);


/// @brief Actualizeaza o masina existenta in colectie pe baza numarului matricol
/// @param colectie - pointer la colectia de masini in care va fi actualizata masina
/// @param nr_matricol - numarul matricol al masinii care va fi actualizata
/// @param model_actualizat - noul model al masinii care va fi actualizata
/// @param categorie_actualizata - noua categorie a masinii care va fi actualizata
/// @param inchiriata_actualizat - noua valoare pentru campul inchiriata al masinii care va fi actualizata
/// @return 1 daca actualizarea a fost realizata cu succes, 0 daca masina cu nr_matricol nu a fost gasita, -1 daca exista o eroare (de exemplu, colectia este nula)
int update(ColectieMasini *colectie, char *nr_matricol, char *model_actualizat, char *categorie_actualizata, int inchiriata_actualizat);


/// @brief Returneaza toate masinile din colectie
/// @param colectie - pointer la colectia de masini din care se vor returna masinile
/// @return - pointer la un array de masini care contine toate masinile din colectie
Masina *get_all_masini(ColectieMasini *colectie);



void destroy_colectie(ColectieMasini *colectie);

#endif