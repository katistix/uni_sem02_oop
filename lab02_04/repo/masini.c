#include "masini.h"
#include <stdlib.h>
#include <string.h>


void initialize_colectie(ColectieMasini *colectie) {
  if (colectie == NULL)
    return; // ne asiguram ca nu incercam sa accesam un null pointer

  colectie->capacity =
      INITIAL_CAPACITY; // capacitatea initiala a colectiei de masini
  colectie->count = 0;  // initial nu avem nicio masina in colectie

  // alocam memorie pentru capacitatea initiala a colectiei
  colectie->masini = (Masina *)malloc(colectie->capacity * sizeof(Masina));
}


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

int get_masina_by_nr_matricol(ColectieMasini *colectie, char *nr_matricol, Masina *rezultat) {
  if (colectie == NULL || nr_matricol == NULL || rezultat == NULL)
    return 0;

  for (int i = 0; i < colectie->count; i++) {
    if (strcmp(colectie->masini[i].nr_matricol, nr_matricol) == 0) {
      *rezultat = colectie->masini[i];
      return 1;
    }
  }
  return 0;
}

int update(ColectieMasini *colectie, char *nr_matricol, char *model_actualizat, char *categorie_actualizata, int inchiriata_actualizat) {
  // ne asiguram ca nu este nula colectia
  if (colectie == NULL)
    return -1; // eroare: colectia este nula


  // cautam masina cu nr_matricol in colectie si o actualizam
  for (int i = 0; i < colectie->count; i++) {
    if (strcmp(colectie->masini[i].nr_matricol, nr_matricol) == 0) {
      strcpy(colectie->masini[i].model, model_actualizat);
      strcpy(colectie->masini[i].categorie, categorie_actualizata);
      colectie->masini[i].inchiriata = inchiriata_actualizat;
      return 1; // actualizare reusita
    }
  }

  return 0; // masina cu nr_matricol nu a fost gasita
}


Masina *get_all_masini(ColectieMasini *colectie) {
  if (colectie == NULL)
    return NULL;

  return colectie->masini;
}

void destroy_colectie(ColectieMasini *colectie) {
  if (colectie == NULL)
    return;
  free(colectie->masini);
}