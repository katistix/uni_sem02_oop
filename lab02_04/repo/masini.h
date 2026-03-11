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
void initialize_colectie(ColectieMasini *colectie);



/// @brief Adauga o masina in colectia de masini
/// @param colectie - pointer la colectia de masini in care va fi adaugata masina
/// @param masina_noua - masina care va fi adaugata
void add(ColectieMasini *colectie, Masina masina_noua);


/// @brief Returneaza toate masinile din colectie
/// @param colectie - pointer la colectia de masini din care se vor returna masinile
/// @return - pointer la un array de masini care contine toate masinile din colectie
Masina *get_all_masini(ColectieMasini *colectie);

// "destructor"
// momentan nu

#endif