/*
4. Inchiriere masini
Creati o aplicatie pentru o firma de inchirieri auto. Fiecare masina are un
numar de inmatriculare, model si categorie (mini, sport, suv, etc). Aplicatia
permite: a) adaugare de masini b) actualizare masina existenta c) inchiriere
masina/returnare masina d) Vizualizare masini dupa un criteru dat (categorie,
model) e) Permite sortarea masinilor dupa: model sau categorie
(crescator/descrescator)
*/

#include "repo/masini.h"
#include "service/masina_service.h"
#include "ui/ui.h"

int main() {
  ColectieMasini colectie;
  initialize_colectie(&colectie);

  MasinaService service;
  initialize_service(&service, &colectie);

  run(&service);

  destroy_colectie(&colectie);
}
