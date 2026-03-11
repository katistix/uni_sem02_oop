#ifndef MASINA_DOMAIN_H
#define MASINA_DOMAIN_H


typedef struct {
  char nr_matricol[7+1]; // sir static, toate numerele matricole o sa fie de forma
                       // "AA12ABC"
  char model[50];      // sir dinamic de caractere pt modelul masinii
  char categorie[50];  // sir dinamic de caractere pt categoria masinii
} Masina;

void print_masina(Masina masina);

#endif