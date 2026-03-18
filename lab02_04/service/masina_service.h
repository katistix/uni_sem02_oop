#ifndef MASINA_SERVICE_H
#define MASINA_SERVICE_H

#include "../domain/masina.h"
#include "../repo/masini.h"

typedef struct {
  ColectieMasini *repo;
} MasinaService;


/// @brief Initializeaza serviciul de masini cu repository-ul dat (constructor)
/// @param srv - pointer la serviciul de masini care va fi initializat
/// @param repo - pointer la repository-ul de masini care va fi folosit de serviciu
void initialize_service(MasinaService *srv, ColectieMasini *repo);


/// @brief Adauga o masina noua in colectia de masini prin intermediul serviciului
/// @param srv - pointer la serviciul de masini care va gestiona adaugarea
/// @param nr_matricol - numarul matricol al masinii care va fi adaugata
/// @param model - modelul masinii care va fi adaugata
/// @param categorie - categoria masinii care va fi adaugata
void srv_add_masina(MasinaService *srv, char *nr_matricol, char *model, char *categorie);


/// @brief Actualizeaza informatiile unei masini existente in colectie prin intermediul serviciului
/// @param srv - pointer la serviciul de masini care va gestiona actualizarea
/// @param nr_matricol - numarul matricol al masinii care va fi actualizata
/// @param model_actualizat - noul model al masinii care va fi actualizata
/// @param categorie_actualizata - noua categorie a masinii care va fi actualizata
/// @return - 1 daca masina a fost gasita si actualizata, 0 daca masina nu a fost gasita
int srv_update_masina_info(MasinaService *srv, char *nr_matricol, char *model_actualizat, char *categorie_actualizata);


/// @brief Schimba starea de `inchiriata` a unei masini existente in colectie prin intermediul serviciului
/// @param srv - pointer la serviciul de masini care va gestiona schimbarea
/// @param nr_matricol - numarul matricol al masinii pentru care va fi schimbata starea
/// @return - 1 daca masina a fost gasita si actualizata, 0 daca masina nu a fost gasita
int srv_toggle_inchiriata(MasinaService *srv, char *nr_matricol);


/// @brief Returneaza toate masinile din colectia gestionata de serviciu
/// @param srv - pointer la serviciul de masini care va returna masinile
/// @return - pointer la un array de masini care contine toate masinile din colectie
Masina *srv_get_all_masini(MasinaService *srv);

/// @brief Returneaza numarul de masini din colectia gestionata de serviciu
/// @param srv - pointer la serviciul de masini care va returna numarul de masini
/// @return - numarul de masini din colectie
int srv_get_count(MasinaService *srv);


/// @brief Returneaza un array de masini sortat dupa un criteriu dat
/// @param srv - pointer la serviciul de masini
/// @param compare_func - functia de comparare care defineste criteriul de sortare
/// @param descending - 0 pentru ordine ascendenta, 1 pentru ordine descendenta
/// @return - pointer la un array de masini sortat
Masina *srv_get_sorted_masini(MasinaService *srv, int (*compare_func)(const void*, const void*), int descending);
#endif
