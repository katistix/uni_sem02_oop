#include "masina_service.h"
#include <string.h>

/// @brief Initializeaza serviciul de masini cu repository-ul dat (constructor)
/// @param srv - pointer la serviciul de masini care va fi initializat
/// @param repo - pointer la repository-ul de masini care va fi folosit de serviciu
void initialize_service(MasinaService *srv, ColectieMasini *repo) {
  srv->repo = repo;
}

/// @brief Adauga o masina noua in colectia de masini prin intermediul serviciului
/// @param srv - pointer la serviciul de masini care va gestiona adaugarea
/// @param nr_matricol - numarul matricol al masinii care va fi adaugata
/// @param model - modelul masinii care va fi adaugata
/// @param categorie - categoria masinii care va fi adaugata
void srv_add_masina(MasinaService *srv, char *nr_matricol, char *model,
                    char *categorie) {
  Masina masina_noua;
  strncpy(masina_noua.nr_matricol, nr_matricol,
          sizeof(masina_noua.nr_matricol) - 1);
  masina_noua.nr_matricol[sizeof(masina_noua.nr_matricol) - 1] = '\0';

  strncpy(masina_noua.model, model, sizeof(masina_noua.model) - 1);
  masina_noua.model[sizeof(masina_noua.model) - 1] = '\0';

  strncpy(masina_noua.categorie, categorie, sizeof(masina_noua.categorie) - 1);
  masina_noua.categorie[sizeof(masina_noua.categorie) - 1] = '\0';

  add(srv->repo, masina_noua);
}

/// @brief Returneaza toate masinile din colectia gestionata de serviciu
/// @param srv - pointer la serviciul de masini care va returna masinile
/// @return - pointer la un array de masini care contine toate masinile din colectie
Masina *srv_get_all_masini(MasinaService *srv) {
  return get_all_masini(srv->repo);
}

/// @brief Returneaza numarul de masini din colectia gestionata de serviciu
/// @param srv - pointer la serviciul de masini care va returna numarul de masini
/// @return - numarul de masini din colectie
int srv_get_count(MasinaService *srv) { return srv->repo->count; }
