#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tranzactie.h"
#include "vector.h"
#include "repo.h"
#include "service.h"

/* ============================================================
 * test_all.c - Test Driven Development (TDD)
 * Fiecare functie din aplicatie este testata individual.
 * Coverage tinta: >= 99% (exclusiv ui.c si main.c)
 * ============================================================ */

/* ================================================================
 * 1. TESTE TRANZACTIE
 * ================================================================ */
static void test_tranzactie(void)
{
    printf("Rulez teste TRANZACTIE...\n");

    /* Constructor si getteri */
    Tranzactie t = tranzactie_creeaza(1, 15, 200.50, "intrare", "Salariu");
    assert(tranzactie_get_id(&t) == 1);
    assert(tranzactie_get_zi(&t) == 15);
    assert(tranzactie_get_suma(&t) == 200.50);
    assert(strcmp(tranzactie_get_tip(&t), "intrare") == 0);
    assert(strcmp(tranzactie_get_descriere(&t), "Salariu") == 0);

    /* Setteri */
    tranzactie_set_zi(&t, 20);
    assert(tranzactie_get_zi(&t) == 20);

    tranzactie_set_suma(&t, 500.0);
    assert(tranzactie_get_suma(&t) == 500.0);

    tranzactie_set_tip(&t, "iesire");
    assert(strcmp(tranzactie_get_tip(&t), "iesire") == 0);

    tranzactie_set_descriere(&t, "Chirie");
    assert(strcmp(tranzactie_get_descriere(&t), "Chirie") == 0);

    /* Validari */
    assert(tranzactie_valid_zi(1));
    assert(tranzactie_valid_zi(31));
    assert(!tranzactie_valid_zi(0));
    assert(!tranzactie_valid_zi(32));

    assert(tranzactie_valid_suma(0.01));
    assert(!tranzactie_valid_suma(0.0));
    assert(!tranzactie_valid_suma(-5.0));

    assert(tranzactie_valid_tip("intrare"));
    assert(tranzactie_valid_tip("iesire"));
    assert(!tranzactie_valid_tip("altceva"));
    assert(!tranzactie_valid_tip(""));

    /* tranzactie_afiseaza - acopera ramura anterior neacoperita */
    Tranzactie ta = tranzactie_creeaza(42, 7, 123.45, "intrare", "Test afisare");
    tranzactie_afiseaza(&ta);
    assert(1); /* asigura ca nu crapa afisarea */

    /* Stringuri lungi - trunchiere */
    char tip_lung[64];
    memset(tip_lung, 'x', sizeof(tip_lung) - 1);
    tip_lung[sizeof(tip_lung) - 1] = '\0';
    tranzactie_set_tip(&t, tip_lung);
    assert((int)strlen(tranzactie_get_tip(&t)) == TIP_MAX - 1);

    char desc_lung[256];
    memset(desc_lung, 'a', sizeof(desc_lung) - 1);
    desc_lung[sizeof(desc_lung) - 1] = '\0';
    tranzactie_set_descriere(&t, desc_lung);
    assert((int)strlen(tranzactie_get_descriere(&t)) == DESC_MAX - 1);

    Tranzactie tl = tranzactie_creeaza(99, 1, 1.0, tip_lung, desc_lung);
    assert((int)strlen(tl.tip) == TIP_MAX - 1);
    assert((int)strlen(tl.descriere) == DESC_MAX - 1);
}

/* ================================================================
 * 2. TESTE VECTOR DINAMIC
 * ================================================================ */
static void test_vector(void)
{
    printf("Rulez teste VECTOR DINAMIC...\n");

    Vector *v = vector_creeaza();
    assert(v != NULL);
    assert(vector_lungime(v) == 0);

    /* Adaugare */
    Tranzactie t1 = tranzactie_creeaza(1, 5,  100.0, "intrare", "A");
    Tranzactie t2 = tranzactie_creeaza(2, 10, 200.0, "iesire",  "B");
    Tranzactie t3 = tranzactie_creeaza(3, 15, 300.0, "intrare", "C");

    assert(vector_adauga(v, t1));
    assert(vector_lungime(v) == 1);
    assert(vector_adauga(v, t2));
    assert(vector_adauga(v, t3));
    assert(vector_lungime(v) == 3);

    /* Acces */
    assert(vector_get(v, 0)->suma == 100.0);
    assert(vector_get(v, 1)->suma == 200.0);
    assert(vector_get(v, 2)->suma == 300.0);
    assert(vector_get(v, -1) == NULL);
    assert(vector_get(v, 3)  == NULL);

    /* Seteaza */
    Tranzactie t4 = tranzactie_creeaza(4, 20, 400.0, "iesire", "D");
    assert(vector_seteaza(v, 1, t4));
    assert(vector_get(v, 1)->suma == 400.0);

    /* Seteaza invalid */
    assert(!vector_seteaza(v, -1, t4));
    assert(!vector_seteaza(v, 99, t4));

    /* Stergere la mijloc */
    assert(vector_sterge(v, 1));
    assert(vector_lungime(v) == 2);
    assert(vector_get(v, 1)->suma == 300.0);

    /* Stergere invalida */
    assert(!vector_sterge(v, -1));
    assert(!vector_sterge(v, 99));

    /* Copie */
    Vector *c = vector_copie(v);
    assert(c != NULL);
    assert(vector_lungime(c) == vector_lungime(v));
    assert(vector_get(c, 0)->suma == vector_get(v, 0)->suma);
    vector_distruge(c);

    /* Gestionare NULL */
    assert(vector_copie(NULL) == NULL);
    assert(vector_lungime(NULL) == 0);
    assert(!vector_adauga(NULL, t1));
    assert(vector_get(NULL, 0) == NULL);
    assert(!vector_sterge(NULL, 0));
    assert(!vector_seteaza(NULL, 0, t1));

    /* distruge NULL nu crapa */
    vector_distruge(NULL);
    assert(1);

    /* Test realocare dinamica - adauga peste CAPACITATE_INITIALA */
    Vector *vd = vector_creeaza();
    int i;
    for (i = 0; i < 20; i++) {
        Tranzactie tx = tranzactie_creeaza(i, i % 31 + 1,
                                        (i + 1) * 10.0,
                                        "intrare", "test");
        vector_adauga(vd, tx);
    }
    assert(vector_lungime(vd) == 20);
    assert(vector_get(vd, 19)->suma == 200.0);
    vector_distruge(vd);

    vector_distruge(v);
}

/* ================================================================
 * 3. TESTE REPO
 * ================================================================ */
static void test_repo(void)
{
    printf("Rulez teste REPO...\n");

    Repo *r = repo_creeaza();
    assert(r != NULL);
    assert(repo_contor(r) == 0);

    Tranzactie t1 = tranzactie_creeaza(0, 5,  150.0, "intrare", "X");
    Tranzactie t2 = tranzactie_creeaza(0, 12, 250.0, "iesire",  "Y");

    assert(repo_adauga(r, t1));
    assert(repo_contor(r) == 1);
    assert(repo_adauga(r, t2));
    assert(repo_contor(r) == 2);

    /* ID-uri auto-incrementate */
    assert(repo_gaseste_dupa_id(r, 1) != NULL);
    assert(repo_gaseste_dupa_id(r, 2) != NULL);
    assert(repo_gaseste_dupa_id(r, 99) == NULL);

    /* Valori stocate */
    Tranzactie *g = repo_gaseste_dupa_id(r, 1);
    assert(g->suma == 150.0);

    /* repo_urmatorul_id */
    assert(repo_urmatorul_id(r) == 3);
    assert(repo_urmatorul_id(NULL) == -1);

    /* Functii cu NULL */
    assert(repo_get_toate(NULL) == NULL);
    assert(repo_contor(NULL) == 0);
    assert(!repo_adauga(NULL, t1));
    assert(repo_gaseste_dupa_id(NULL, 1) == NULL);
    assert(repo_index_dupa_id(NULL, 1) == -1);

    /* repo_index_dupa_id */
    assert(repo_index_dupa_id(r, 1) == 0);
    assert(repo_index_dupa_id(r, 2) == 1);
    assert(repo_index_dupa_id(r, 99) == -1);

    /* Modificare */
    assert(repo_modifica(r, 1, 8, 999.0, "iesire", "Nou"));
    g = repo_gaseste_dupa_id(r, 1);
    assert(g->zi == 8);
    assert(g->suma == 999.0);
    assert(strcmp(g->tip, "iesire") == 0);
    assert(!repo_modifica(r, 99, 1, 1.0, "intrare", "x"));

    /* Stergere */
    assert(repo_sterge_dupa_id(r, 1));
    assert(repo_contor(r) == 1);
    assert(!repo_sterge_dupa_id(r, 99));

    /* distruge NULL nu crapa */
    repo_distruge(NULL);
    assert(1);

    repo_distruge(r);
}

/* ================================================================
 * 4. TESTE SERVICE
 * ================================================================ */
static void test_service(void)
{
    printf("Rulez teste SERVICE...\n");

    Repo    *r = repo_creeaza();
    Service *s = service_creeaza(r);
    assert(s != NULL);
    assert(service_contor(s) == 0);

    /* Adaugare valida */
    assert(service_adauga(s, 5,  100.0, "intrare", "Salariu") == 1);
    assert(service_adauga(s, 10, 200.0, "iesire",  "Chirie")  == 1);
    assert(service_adauga(s, 15,  50.0, "intrare", "Bonus")   == 1);
    assert(service_adauga(s, 20, 300.0, "iesire",  "Masina")  == 1);
    assert(service_contor(s) == 4);

    /* Validare - date invalide */
    assert(service_adauga(s,  0, 100.0, "intrare", "X") == -2);
    assert(service_adauga(s, 32, 100.0, "intrare", "X") == -2);
    assert(service_adauga(s, 5,    0.0, "intrare", "X") == -2);
    assert(service_adauga(s, 5,  -50.0, "intrare", "X") == -2);
    assert(service_adauga(s, 5,  100.0, "altul",   "X") == -2);
    assert(service_contor(s) == 4);

    /* NULL guards */
    assert(service_adauga(NULL, 5, 100.0, "intrare", "X") == -1);
    assert(service_modifica(NULL, 1, 5, 10.0, "intrare", "X") == -1);
    assert(service_sterge(NULL, 1) == -1);

    /* Modificare */
    assert(service_modifica(s, 1, 7, 999.0, "iesire", "Nou") == 1);
    assert(service_modifica(s, 99, 1, 10.0, "intrare", "X") == -3);
    assert(service_modifica(s, 1, 0, 10.0, "intrare", "X")  == -2);

    /* Stergere */
    assert(service_sterge(s, 3) == 1);
    assert(service_contor(s) == 3);
    assert(service_sterge(s, 99) == -2);

    /* Filtrare dupa tip */
    Vector *iesiri  = service_filtreaza_tip(s, "iesire");
    Vector *intrari = service_filtreaza_tip(s, "intrare");
    assert(vector_lungime(iesiri) == 3);
    assert(vector_lungime(intrari) == 0);
    vector_distruge(iesiri);
    vector_distruge(intrari);

    /* Adaugam intrari pentru filtre suma */
    service_adauga(s, 1,  50.0, "intrare", "Test");
    service_adauga(s, 2, 150.0, "intrare", "Test2");

    Vector *mari = service_filtreaza_suma_mai_mare(s, 100.0);
    Vector *mici = service_filtreaza_suma_mai_mica(s, 100.0);
    assert(vector_lungime(mari) >= 2);
    assert(vector_lungime(mici) >= 1);
    vector_distruge(mari);
    vector_distruge(mici);

    /* Sortare */
    Vector *sa = service_sorteaza_suma_asc(s);
    assert(sa != NULL);
    int n = vector_lungime(sa), ok_asc = 1;
    int i;
    for (i = 0; i < n - 1; i++)
        if (vector_get(sa, i)->suma > vector_get(sa, i+1)->suma) { ok_asc = 0; break; }
    assert(ok_asc);
    vector_distruge(sa);

    Vector *sd = service_sorteaza_suma_desc(s);
    int ok_desc = 1;
    n = vector_lungime(sd);
    for (i = 0; i < n - 1; i++)
        if (vector_get(sd, i)->suma < vector_get(sd, i+1)->suma) { ok_desc = 0; break; }
    assert(ok_desc);
    vector_distruge(sd);

    Vector *za = service_sorteaza_zi_asc(s);
    int ok_zi_asc = 1;
    n = vector_lungime(za);
    for (i = 0; i < n - 1; i++)
        if (vector_get(za, i)->zi > vector_get(za, i+1)->zi) { ok_zi_asc = 0; break; }
    assert(ok_zi_asc);
    vector_distruge(za);

    Vector *zd = service_sorteaza_zi_desc(s);
    int ok_zi_desc = 1;
    n = vector_lungime(zd);
    for (i = 0; i < n - 1; i++)
        if (vector_get(zd, i)->zi < vector_get(zd, i+1)->zi) { ok_zi_desc = 0; break; }
    assert(ok_zi_desc);
    vector_distruge(zd);

    /* service_get_toate */
    Vector *toate = service_get_toate(s);
    assert(toate != NULL);
    assert(vector_lungime(toate) == service_contor(s));

    /* service_distruge NULL nu crapa */
    service_distruge(NULL);
    assert(1);

    service_distruge(s);
    repo_distruge(r);
}

/* ================================================================
 * RUNNER TESTE
 * ================================================================ */
void run_all_tests(void)
{
    printf("\n--- START SUITE DE TESTE TDD (ASSERT) ---\n");

    test_tranzactie();
    test_vector();
    test_repo();
    test_service();

    printf("--- TOATE TESTELE AU TRECUT CU SUCCES! ---\n\n");
}

int main(void)
{
    run_all_tests();
    return 0;
}