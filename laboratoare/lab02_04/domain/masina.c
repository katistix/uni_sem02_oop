#include <stdio.h>
#include <stdlib.h>

#include "masina.h"


// Printeaza o masina in formatul specificat
void print_masina(Masina masina) {
  printf("{nr_matricol: %s, model: %s, categorie: %s, inchiriata: %d}\n", masina.nr_matricol,
         masina.model, masina.categorie, masina.inchiriata);
}