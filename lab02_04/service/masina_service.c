#include "masina_service.h"
#include <string.h>
#include <stdlib.h>

// UTILS:

/// @brief Compara doua masini dupa model pentru a fi folosita in sortare
/// @param a 
/// @param b 
/// @return 1 daca modelul masinii_a > modelul masinii_b, -1 daca modelul masinii_a < modelul masinii_b, 0 daca sunt egale
int compare_by_model(const void *a, const void *b) {
  const Masina *masina_a = (const Masina *)a;
  const Masina *masina_b = (const Masina *)b;
  return strcmp(masina_a->model, masina_b->model);
}

/// @brief Compara doua masini dupa categorie pentru a fi folosita in sortare
/// @param a 
/// @param b 
/// @return 1 daca masina_a > masina_b, -1 daca masina_a < masina_b, 0 daca sunt egale
int compare_by_categorie(const void *a, const void *b) {
  const Masina *masina_a = (const Masina *)a;
  const Masina *masina_b = (const Masina *)b;
  return strcmp(masina_a->categorie, masina_b->categorie);
}




// Service implementation:


void initialize_service(MasinaService *srv, ColectieMasini *repo) {
  srv->repo = repo;
}


void srv_add_masina(MasinaService *srv, char *nr_matricol, char *model, char *categorie) {
  Masina masina_noua;

  // Copiem datele in structura masina_noua, asigurandu-ne ca nu depasim dimensiunile campurilor

  strncpy(masina_noua.nr_matricol, nr_matricol, sizeof(masina_noua.nr_matricol) - 1);
  masina_noua.nr_matricol[sizeof(masina_noua.nr_matricol) - 1] = '\0';

  strncpy(masina_noua.model, model, sizeof(masina_noua.model) - 1);
  masina_noua.model[sizeof(masina_noua.model) - 1] = '\0';

  strncpy(masina_noua.categorie, categorie, sizeof(masina_noua.categorie) - 1);
  masina_noua.categorie[sizeof(masina_noua.categorie) - 1] = '\0';

  masina_noua.inchiriata = 0; // default value
  // Adaugam masina noua in colectie prin intermediul repository-ului
  add(srv->repo, masina_noua);
}


int srv_update_masina_info(MasinaService *srv, char *nr_matricol, char *model_actualizat, char *categorie_actualizata) {
  Masina m;
  if (get_masina_by_nr_matricol(srv->repo, nr_matricol, &m)) {
    update(srv->repo, nr_matricol, model_actualizat, categorie_actualizata, m.inchiriata);
    return 1;
  }
  return 0;
}

int srv_toggle_inchiriata(MasinaService *srv, char *nr_matricol) {
  Masina m;
  if (get_masina_by_nr_matricol(srv->repo, nr_matricol, &m)) {
    update(srv->repo, nr_matricol, m.model, m.categorie, !m.inchiriata);
    return 1;
  }
  return 0;
}


Masina *srv_get_all_masini(MasinaService *srv) {
  return get_all_masini(srv->repo);
}


int srv_get_count(MasinaService *srv) {
  return srv->repo->count;
}


Masina *srv_get_sorted_by_model(MasinaService *srv) {
  int count = srv_get_count(srv);

  // alocam memorie pentru un array de masini sortat
  Masina *sorted_masini = malloc(count * sizeof(Masina));

  // Copiem masinile din colectie in array-ul ce va fi sortat
  memcpy(sorted_masini, get_all_masini(srv->repo), count * sizeof(Masina));

  // Sortam array-ul de masini dupa model
  // Folosim mergesort din stdlib
  mergesort(sorted_masini, count, sizeof(Masina), compare_by_model);

  return sorted_masini;
}

Masina *srv_get_sorted_by_categorie(MasinaService *srv) {
  int count = srv_get_count(srv);

  // alocam memorie pentru un array de masini sortat
  Masina *sorted_masini = malloc(count * sizeof(Masina));

  // Copiem masinile din colectie in array-ul ce va fi sortat
  memcpy(sorted_masini, get_all_masini(srv->repo), count * sizeof(Masina));

  // Sortam array-ul de masini dupa categorie
  // Folosim mergesort din stdlib
  mergesort(sorted_masini, count, sizeof(Masina), compare_by_categorie);

  return sorted_masini;
}



