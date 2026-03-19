#include "masina_compare.h"
#include <string.h>

int compare_by_model(const void *a, const void *b) {
  const Masina *masina_a = (const Masina *)a;
  const Masina *masina_b = (const Masina *)b;
  return strcmp(masina_a->model, masina_b->model);
}

int compare_by_categorie(const void *a, const void *b) {
  const Masina *masina_a = (const Masina *)a;
  const Masina *masina_b = (const Masina *)b;
  return strcmp(masina_a->categorie, masina_b->categorie);
}
