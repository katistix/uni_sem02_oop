#include "masini.h"
#include <stdlib.h>
#include <string.h>

/// @brief Initializeaza colectia de masini cu o capacitate initiala si aloca memorie pentru array-ul de masini
/// @param colectie - pointer la colectia de masini care va fi initializata
void initialize_colectie(ColectieMasini *colectie) {
  if (colectie == NULL)
    return; // ne asiguram ca nu incercam sa accesam un null pointer

  colectie->capacity =
      INITIAL_CAPACITY; // capacitatea initiala a colectiei de masini
  colectie->count = 0;  // initial nu avem nicio masina in colectie

  // alocam memorie pentru capacitatea initiala a colectiei
  colectie->masini = (Masina *)malloc(colectie->capacity * sizeof(Masina));
}

/// @brief Adauga o masina in colectia de masini
/// @param colectie - pointer la colectia de masini in care va fi adaugata masina
/// @param masina_noua - masina care va fi adaugata
void add(ColectieMasini *colectie, Masina masina_noua) {
  if (colectie == NULL)
    return;

  // daca nu incape, crestem capacitatea
  if (colectie->count == colectie->capacity) {
    int new_capacity =
        colectie->capacity * CAPACITY_RESIZE_FACTOR; // dublam capacitatea
    // realocam memorie in functie de noua capacitate
    Masina *temp = realloc(colectie->masini, new_capacity * sizeof(Masina));
    if (temp) {
      colectie->masini = temp;
      colectie->capacity = new_capacity;
    }
  }

  // inseram noua masina
  colectie->masini[colectie->count] = masina_noua;
  colectie->count++;
}

/// @brief Returneaza toate masinile din colectie
/// @param colectie - pointer la colectia de masini din care se vor returna masinile
/// @return - pointer la un array de masini care contine toate masinile din colectie
Masina *get_all_masini(ColectieMasini *colectie) {
  if (colectie == NULL)
    return NULL;

  return colectie->masini;
}