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

static void merge(Masina *arr, int left, int mid, int right, int (*compare_func)(const void*, const void*)) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  Masina *left_arr = malloc(n1 * sizeof(Masina));
  Masina *right_arr = malloc(n2 * sizeof(Masina));

  for (int i = 0; i < n1; i++)
    left_arr[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    right_arr[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (compare_func(&left_arr[i], &right_arr[j]) <= 0) {
      arr[k] = left_arr[i];
      i++;
    } else {
      arr[k] = right_arr[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = left_arr[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = right_arr[j];
    j++;
    k++;
  }

  free(left_arr);
  free(right_arr);
}

static void merge_sort(Masina *arr, int left, int right, int (*compare_func)(const void*, const void*)) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid, compare_func);
    merge_sort(arr, mid + 1, right, compare_func);
    merge(arr, left, mid, right, compare_func);
  }
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


Masina *srv_get_sorted_masini(MasinaService *srv, int (*compare_func)(const void*, const void*), int descending) {
  int count = srv_get_count(srv);

  Masina *sorted_masini = malloc(count * sizeof(Masina));

  memcpy(sorted_masini, get_all_masini(srv->repo), count * sizeof(Masina));

  if (descending) {
    qsort(sorted_masini, count, sizeof(Masina), compare_func);
    for (int i = 0; i < count / 2; i++) {
      Masina temp = sorted_masini[i];
      sorted_masini[i] = sorted_masini[count - 1 - i];
      sorted_masini[count - 1 - i] = temp;
    }
  } else {
    merge_sort(sorted_masini, 0, count - 1, compare_func);
  }

  return sorted_masini;
}

Masina *srv_get_sorted_by_model(MasinaService *srv) {
  return srv_get_sorted_masini(srv, compare_by_model, 0);
}

Masina *srv_get_sorted_by_categorie(MasinaService *srv) {
  return srv_get_sorted_masini(srv, compare_by_categorie, 0);
}



