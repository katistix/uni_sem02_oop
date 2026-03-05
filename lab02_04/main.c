/*
4. Inchiriere masini
Creati o aplicatie pentru o firma de inchirieri auto. Fiecare masina are un
numar de inmatriculare, model si categorie (mini, sport, suv, etc). Aplicatia
permite: a) adaugare de masini b) actualizare masina existenta c) inchiriere
masina/returnare masina d) Vizualizare masini dupa un criteru dat (categorie,
model) e) Permite sortarea masinilor dupa: model sau categorie
(crescator/descrescator)

*/

#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nr_matricol[7]; // sir static, toate numerele matricole o sa fie de forma
                       // "AA12ABC"
  char model[50];      // sir dinamic de caractere pt modelul masinii
  char categorie[50];  // sir dinamic de caractere pt categoria masinii
} Masina;

typedef struct {
  Masina *masini;
  int capacity; // capacitatea colectiei
  int count;    // cate masini sunt in colectie
} ColectieMasini;

// HELPERS

void read_string(char *dest, int size) {
  if (fgets(dest, size, stdin)) {
    // remove trailing newline if it exists
    dest[strcspn(dest, "\n")] =
        0; // replace the newline with the null terminator
  }
}

void print_masina(Masina masina) {
  printf("{nr_matricol: %s, model: %s, categorie: %s}\n", masina.nr_matricol,
         masina.model, masina.categorie);
}

void initialize_colectie(ColectieMasini *colectie) {
  if (colectie == NULL)
    return; // ne asiguram ca nu incercam sa accesam un null pointer

  colectie->capacity = 10; // capacitatea initiala a colectiei de masini
  colectie->count = 0;     // initial nu avem nicio masina in colectie
  // alocam memorie pentru capacitatea initiala a colectiei
  colectie->masini = (Masina *)malloc(colectie->capacity * sizeof(Masina));
}

void add(ColectieMasini *colectie, Masina masina_noua) {
  if (colectie == NULL)
    return;

  // daca nu incape, crestem capacitatea
  if (colectie->count == colectie->capacity) {
    int new_capacity = colectie->capacity * 2; // dublam capacitatea
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

// COMENZI

void listare_masini(ColectieMasini *colectie) {
  if (colectie->count == 0) {
    printf("Nu exista masini in colecte!\n");
    return;
  }
  for (int i = 0; i < colectie->count; i++) {
    print_masina(colectie->masini[i]);
  }
}

void adaugare_masini(ColectieMasini *colectie) {
  Masina masina_noua;

  printf("Numar matricol: ");
  read_string(masina_noua.nr_matricol, sizeof(masina_noua.nr_matricol));

  printf("Model: ");
  read_string(masina_noua.model, sizeof(masina_noua.model));

  printf("categorie: ");
  read_string(masina_noua.categorie, sizeof(masina_noua.categorie));

  add(colectie, masina_noua);

  printf("Masina a fost adaugata cu succes!\n");
}

void print_menu() {

  // print the menu
  printf("=== MENIU ===\n");
  printf("1. Listare masini\n");
  printf("2. Adaugare masina\n");
}

int get_menu_option() {
  char buffer[10];
  printf(">>> ");
  if (fgets(buffer, sizeof(buffer), stdin)) {
    return atoi(buffer);
  }
  return -1;
}

int main() {
  ColectieMasini colectie;
  initialize_colectie(&colectie);

  int running = 1;
  while (running) {
    print_menu();
    int menu_option = get_menu_option();
    printf("%d", menu_option);
    switch (menu_option) {
    case 1:
      listare_masini(&colectie);
      break;
    case 2:
      adaugare_masini(&colectie);
      break;
    case 0:
      running = 0;
      break;
    default:
      printf("Optiune invalida!\n");
      break;
    }
  }

  printf("la revedere!\n");
}
