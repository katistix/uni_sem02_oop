#ifndef MASINA_SERVICE_H
#define MASINA_SERVICE_H

#include "../domain/masina.h"
#include "../repo/masini.h"

typedef struct {
  ColectieMasini *repo;
} MasinaService;

void initialize_service(MasinaService *srv, ColectieMasini *repo);
void srv_add_masina(MasinaService *srv, char *nr_matricol, char *model,
                    char *categorie);
Masina *srv_get_all_masini(MasinaService *srv);
int srv_get_count(MasinaService *srv);

#endif
