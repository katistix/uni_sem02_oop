#include "../repo/masini.h"
#include "../service/masina_service.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Repo tests

void test_domain_masina() {
  printf("test_domain_masina...\n");
  Masina masina = {"TM10ABC", "Dacia", "sedan"};
  print_masina(masina);
  printf("test_domain_masina passed!\n");
}

void test_repo_initialize_colectie() {
  printf("test_repo_initialize_colectie...\n");

  ColectieMasini colectie;
  initialize_colectie(NULL); // test null
  initialize_colectie(&colectie);
  assert(colectie.capacity == INITIAL_CAPACITY);
  assert(colectie.count == 0);
  assert(colectie.masini != NULL);

  printf("test_repo_initialize_colectie passed!\n");
}

void test_repo_add() {
  printf("test_repo_add...\n");

  add(NULL, (Masina){"XX11YYY", "X", "Y"}); // test null

  ColectieMasini colectie;
  initialize_colectie(&colectie);

  Masina masina1 = {"AA12ABC", "model1", "categorie1"};
  add(&colectie, masina1);
  assert(colectie.count == 1);
  assert(strcmp(colectie.masini[0].nr_matricol, "AA12ABC") == 0);
  assert(strcmp(colectie.masini[0].model, "model1") == 0);
  assert(strcmp(colectie.masini[0].categorie, "categorie1") == 0);

  // Testam adaugarea a mai multe masini pentru a verifica redimensionarea
  for (int i = 0; i < INITIAL_CAPACITY; i++) {
    Masina masina = {"BB12ABC", "model2", "categorie2"};
    add(&colectie, masina);
  }
  assert(colectie.count == INITIAL_CAPACITY + 1);
  assert(colectie.capacity >= INITIAL_CAPACITY * CAPACITY_RESIZE_FACTOR);

  printf("test_repo_add passed!\n");
}

void test_repo_get_all_masini() {
  printf("test_repo_get_all_masini...\n");

  assert(get_all_masini(NULL) == NULL); // test null

  ColectieMasini colectie;
  initialize_colectie(&colectie);

  Masina masina1 = {"AA12ABC", "model1", "categorie1"};
  add(&colectie, masina1);

  Masina *masini = get_all_masini(&colectie);
  assert(masini != NULL);
  assert(strcmp(masini[0].nr_matricol, "AA12ABC") == 0);
  assert(strcmp(masini[0].model, "model1") == 0);
  assert(strcmp(masini[0].categorie, "categorie1") == 0);

  printf("test_repo_get_all_masini passed!\n");
}

void test_srv_initialize_service() {
  printf("test_srv_initialize_service...\n");
  ColectieMasini colectie;
  initialize_colectie(&colectie);
  MasinaService service;
  initialize_service(&service, &colectie);
  assert(service.repo == &colectie);
  printf("test_srv_initialize_service passed!\n");
}

void test_srv_add_and_get() {
  printf("test_srv_add_and_get...\n");
  ColectieMasini colectie;
  initialize_colectie(&colectie);
  MasinaService service;
  initialize_service(&service, &colectie);

  srv_add_masina(&service, "TM11ABC", "Audi", "sedan");
  assert(srv_get_count(&service) == 1);
  Masina *masini = srv_get_all_masini(&service);
  assert(strcmp(masini[0].nr_matricol, "TM11ABC") == 0);
  assert(strcmp(masini[0].model, "Audi") == 0);
  assert(strcmp(masini[0].categorie, "sedan") == 0);
  printf("test_srv_add_and_get passed!\n");
}

int main() {
  printf("=== rulare teste... ===\n\n");

  test_domain_masina();
  test_repo_initialize_colectie();

  test_repo_add();
  test_repo_get_all_masini();

  test_srv_initialize_service();
  test_srv_add_and_get();

  printf("\n=== teste rulate cu succes! ===\n");

  return 0;
}
