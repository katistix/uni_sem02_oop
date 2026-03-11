#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../domain/masina.h"
#include "../service/masina_service.h"
#include "ui.h"

// helpers
void clear_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void print_menu() {
  printf("=== MENIU ===\n");
  printf("1. Listare masini\n");
  printf("2. Adaugare masina\n");
  printf("0. Iesire\n");
  printf(">>> ");
}

// COMENZI
void command_add_masina(MasinaService *service) {
  char nr_matricol[50];
  char model[50];
  char categorie[50];

  printf("Numar matricol: ");
  fgets(nr_matricol, sizeof(nr_matricol), stdin);
  nr_matricol[strcspn(nr_matricol, "\n")] = 0; // remove newline

  printf("Model: ");
  fgets(model, sizeof(model), stdin);
  model[strcspn(model, "\n")] = 0; // remove newline

  printf("categorie: ");
  fgets(categorie, sizeof(categorie), stdin);
  categorie[strcspn(categorie, "\n")] = 0; // remove newline

  srv_add_masina(service, nr_matricol, model, categorie);

  printf("Masina a fost adaugata cu succes!\n");
}

void command_listare_masini(MasinaService *service) {
  Masina *masini = srv_get_all_masini(service);
  int count = srv_get_count(service);
  for (int i = 0; i < count; i++) {
    print_masina(masini[i]);
  }
}

void run(MasinaService *service) {
  int is_running = 1;
  while (is_running) {
    print_menu();

    // input menu option
    int option = -1;
    int result = scanf("%d", &option);
    if (result != 1) {
      printf("Optiune invalida!\n");
      clear_buffer();
      continue;
    }
    clear_buffer();

    switch (option) {
    case 1:
      command_listare_masini(service);
      break;
    case 2:
      command_add_masina(service);
      break;
    case 0:
      is_running = 0;
      break;
    default:
      printf("Optiune invalida!\n");
    }
  }
}