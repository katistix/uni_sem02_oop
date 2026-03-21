#include <stdio.h>
#include <stdlib.h>
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

    Tranzactie t = tranzactie_creeaza(1, 15, 200.50, "intrare", "Salariu");
    assert(tranzactie_get_id(&t) == 1);
    assert(tranzactie_get_zi(&t) == 15);
    assert(tranzactie_get_suma(&t) == 200.50);
    assert(strcmp(tranzactie_get_tip(&t), "intrare") == 0);
    assert(strcmp(tranzactie_get_descriere(&t), "Salariu") == 0);

    tranzactie_set_zi(&t, 20);
    assert(tranzactie_get_zi(&t) == 20);

    tranzactie_set_suma(&t, 500.0);
    assert(tranzactie_get_suma(&t) == 500.0);

    tranzactie_set_tip(&t, "iesire");
    assert(strcmp(tranzactie_get_tip(&t), "iesire") == 0);

    tranzactie_set_descriere(&t, "Chirie");
    assert(strcmp(tranzactie_get_descriere(&t), "Chirie") == 0);

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

    Tranzactie ta = tranzactie_creeaza(42, 7, 123.45, "intrare", "Test afisare");
    tranzactie_afiseaza(&ta);
    assert(1);

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
 * 2. TESTE VECTOR GENERIC
 * ================================================================ */
static void *tranzactie_copy(const void *p)
{
    const Tranzactie *orig = (const Tranzactie *)p;
    Tranzactie *copy = (Tranzactie *)malloc(sizeof(Tranzactie));
    if (copy) *copy = *orig;
    return copy;
}

static void test_vector(void)
{
    printf("Rulez teste VECTOR GENERIC...\n");

    Vector *v = vector_creeaza(sizeof(Tranzactie), NULL);
    assert(v != NULL);
    assert(vector_lungime(v) == 0);

    Tranzactie t1 = tranzactie_creeaza(1, 5,  100.0, "intrare", "A");
    Tranzactie t2 = tranzactie_creeaza(2, 10, 200.0, "iesire",  "B");
    Tranzactie t3 = tranzactie_creeaza(3, 15, 300.0, "intrare", "C");

    assert(vector_adauga(v, &t1));
    assert(vector_lungime(v) == 1);
    assert(vector_adauga(v, &t2));
    assert(vector_adauga(v, &t3));
    assert(vector_lungime(v) == 3);

    assert(((Tranzactie *)vector_get(v, 0))->suma == 100.0);
    assert(((Tranzactie *)vector_get(v, 1))->suma == 200.0);
    assert(((Tranzactie *)vector_get(v, 2))->suma == 300.0);
    assert(vector_get(v, -1) == NULL);
    assert(vector_get(v, 3)  == NULL);

    Tranzactie t4 = tranzactie_creeaza(4, 20, 400.0, "iesire", "D");
    assert(vector_seteaza(v, 1, &t4));
    assert(((Tranzactie *)vector_get(v, 1))->suma == 400.0);

    assert(!vector_seteaza(v, -1, &t4));

    assert(vector_sterge(v, 1));
    assert(vector_lungime(v) == 2);
    assert(((Tranzactie *)vector_get(v, 1))->suma == 300.0);

    assert(!vector_sterge(v, -1));
    assert(!vector_sterge(v, 99));

    Vector *c = vector_copie(v, tranzactie_copy);
    assert(c != NULL);
    assert(vector_lungime(c) == vector_lungime(v));
    assert(((Tranzactie *)vector_get(c, 0))->suma == ((Tranzactie *)vector_get(v, 0))->suma);
    vector_distruge(c);

    assert(vector_copie(NULL, tranzactie_copy) == NULL);
    assert(vector_copie(v, NULL) == NULL);
    assert(vector_lungime(NULL) == 0);
    assert(!vector_adauga(NULL, &t1));
    assert(vector_get(NULL, 0) == NULL);
    assert(!vector_sterge(NULL, 0));
    assert(!vector_seteaza(NULL, 0, &t1));

    vector_distruge(NULL);
    assert(1);

    Vector *vd = vector_creeaza(sizeof(Tranzactie), NULL);
    int i;
    for (i = 0; i < 20; i++) {
        Tranzactie tx = tranzactie_creeaza(i, i % 31 + 1,
                                        (i + 1) * 10.0,
                                        "intrare", "test");
        vector_adauga(vd, &tx);
    }
    assert(vector_lungime(vd) == 20);
    assert(((Tranzactie *)vector_get(vd, 19))->suma == 200.0);
    vector_distruge(vd);

    vector_distruge(v);
}

/* ================================================================
 * 2b. TESTE VECTOR DE VECTORI (generic, pentru undo)
 * ================================================================ */
static void vector_ptr_destructor(void *p)
{
    vector_distruge(*(Vector **)p);
}

static void test_vv(void)
{
    printf("Rulez teste VECTOR DE VECTORI...\n");

    Vector *vv = vector_creeaza(sizeof(Vector *), vector_ptr_destructor);
    assert(vv != NULL);
    assert(vector_lungime(vv) == 0);

    Vector *v1 = vector_creeaza(sizeof(Tranzactie), NULL);
    Tranzactie tx1 = tranzactie_creeaza(1, 5, 100.0, "intrare", "A");
    vector_adauga(v1, &tx1);

    Vector *v2 = vector_creeaza(sizeof(Tranzactie), NULL);
    Tranzactie tx2a = tranzactie_creeaza(1, 5, 100.0, "intrare", "A");
    Tranzactie tx2b = tranzactie_creeaza(2, 10, 200.0, "iesire", "B");
    vector_adauga(v2, &tx2a);
    vector_adauga(v2, &tx2b);

    Vector *v3 = vector_creeaza(sizeof(Tranzactie), NULL);
    Tranzactie tx3 = tranzactie_creeaza(1, 5, 100.0, "intrare", "A");
    vector_adauga(v3, &tx3);

    Vector **p1 = (Vector **)malloc(sizeof(Vector *));
    *p1 = v1;
    assert(vector_adauga(vv, p1));
    free(p1);
    assert(vector_lungime(vv) == 1);

    Vector **p2 = (Vector **)malloc(sizeof(Vector *));
    *p2 = v2;
    assert(vector_adauga(vv, p2));
    free(p2);
    assert(vector_lungime(vv) == 2);

    Vector **p3 = (Vector **)malloc(sizeof(Vector *));
    *p3 = v3;
    assert(vector_adauga(vv, p3));
    free(p3);
    assert(vector_lungime(vv) == 3);

    Vector **last = (Vector **)vector_get(vv, vector_lungime(vv) - 1);
    assert(last && *last && vector_lungime(*last) == 1);
    vv->lungime--;
    assert(vector_lungime(vv) == 2);

    last = (Vector **)vector_get(vv, vector_lungime(vv) - 1);
    assert(last && *last && vector_lungime(*last) == 2);
    vv->lungime--;
    assert(vector_lungime(vv) == 1);

    p3 = (Vector **)malloc(sizeof(Vector *));
    *p3 = v3;
    vector_adauga(vv, p3);
    free(p3);

    assert(vector_lungime(vv) == 2);
    vector_distruge(vv);
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

    assert(repo_gaseste_dupa_id(r, 1) != NULL);
    assert(repo_gaseste_dupa_id(r, 2) != NULL);
    assert(repo_gaseste_dupa_id(r, 99) == NULL);

    Tranzactie *g = repo_gaseste_dupa_id(r, 1);
    assert(g->suma == 150.0);

    assert(repo_urmatorul_id(r) == 3);
    assert(repo_urmatorul_id(NULL) == -1);

    assert(repo_get_toate(NULL) == NULL);
    assert(repo_contor(NULL) == 0);
    assert(!repo_adauga(NULL, t1));
    assert(repo_gaseste_dupa_id(NULL, 1) == NULL);
    assert(repo_index_dupa_id(NULL, 1) == -1);

    assert(repo_index_dupa_id(r, 1) == 0);
    assert(repo_index_dupa_id(r, 2) == 1);
    assert(repo_index_dupa_id(r, 99) == -1);

    assert(repo_modifica(r, 1, 8, 999.0, "iesire", "Nou"));
    g = repo_gaseste_dupa_id(r, 1);
    assert(g->zi == 8);
    assert(g->suma == 999.0);
    assert(strcmp(g->tip, "iesire") == 0);
    assert(!repo_modifica(r, 99, 1, 1.0, "intrare", "x"));

    assert(repo_sterge_dupa_id(r, 1));
    assert(repo_contor(r) == 1);
    assert(!repo_sterge_dupa_id(r, 99));

    repo_distruge(NULL);
    assert(1);

    Repo *r2 = repo_creeaza();
    assert(r2 != NULL);
    repo_adauga(r2, tranzactie_creeaza(0, 1, 50.0, "intrare", "X"));
    repo_adauga(r2, tranzactie_creeaza(0, 2, 60.0, "intrare", "Y"));
    assert(repo_contor(r2) == 2);

    Vector *backup = vector_copie(repo_get_toate(r2), tranzactie_copy);
    repo_adauga(r2, tranzactie_creeaza(0, 3, 70.0, "intrare", "Z"));
    assert(repo_contor(r2) == 3);

    repo_restore(r2, backup);
    assert(repo_contor(r2) == 2);
    repo_distruge(r2);

    repo_restore(NULL, backup);
    repo_restore(r, NULL);

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

    assert(service_adauga(s, 5,  100.0, "intrare", "Salariu") == 1);
    assert(service_adauga(s, 10, 200.0, "iesire",  "Chirie")  == 1);
    assert(service_adauga(s, 15,  50.0, "intrare", "Bonus")   == 1);
    assert(service_adauga(s, 20, 300.0, "iesire",  "Masina")  == 1);
    assert(service_contor(s) == 4);

    assert(service_adauga(s,  0, 100.0, "intrare", "X") == -2);
    assert(service_adauga(s, 32, 100.0, "intrare", "X") == -2);
    assert(service_adauga(s, 5,    0.0, "intrare", "X") == -2);
    assert(service_adauga(s, 5,  -50.0, "intrare", "X") == -2);
    assert(service_adauga(s, 5,  100.0, "altul",   "X") == -2);
    assert(service_contor(s) == 4);

    assert(service_adauga(NULL, 5, 100.0, "intrare", "X") == -1);
    assert(service_modifica(NULL, 1, 5, 10.0, "intrare", "X") == -1);
    assert(service_sterge(NULL, 1) == -1);

    assert(service_modifica(s, 1, 7, 999.0, "iesire", "Nou") == 1);
    assert(service_modifica(s, 99, 1, 10.0, "intrare", "X") == -3);
    assert(service_modifica(s, 1, 0, 10.0, "intrare", "X")  == -2);

    assert(service_sterge(s, 3) == 1);
    assert(service_contor(s) == 3);
    assert(service_sterge(s, 99) == -2);

    Vector *iesiri  = service_filtreaza_tip(s, "iesire");
    Vector *intrari = service_filtreaza_tip(s, "intrare");
    assert(vector_lungime(iesiri) == 3);
    assert(vector_lungime(intrari) == 0);
    vector_distruge(iesiri);
    vector_distruge(intrari);

    service_adauga(s, 1,  50.0, "intrare", "Test");
    service_adauga(s, 2, 150.0, "intrare", "Test2");

    Vector *mari = service_filtreaza_suma_mai_mare(s, 100.0);
    Vector *mici = service_filtreaza_suma_mai_mica(s, 100.0);
    assert(vector_lungime(mari) >= 2);
    assert(vector_lungime(mici) >= 1);
    vector_distruge(mari);
    vector_distruge(mici);

    Vector *sa = service_sorteaza_suma_asc(s);
    assert(sa != NULL);
    int n = vector_lungime(sa), ok_asc = 1;
    int i;
    for (i = 0; i < n - 1; i++) {
        double a = ((Tranzactie *)vector_get(sa, i))->suma;
        double b = ((Tranzactie *)vector_get(sa, i+1))->suma;
        if (a > b) { ok_asc = 0; break; }
    }
    assert(ok_asc);
    vector_distruge(sa);

    Vector *sd = service_sorteaza_suma_desc(s);
    int ok_desc = 1;
    n = vector_lungime(sd);
    for (i = 0; i < n - 1; i++) {
        double a = ((Tranzactie *)vector_get(sd, i))->suma;
        double b = ((Tranzactie *)vector_get(sd, i+1))->suma;
        if (a < b) { ok_desc = 0; break; }
    }
    assert(ok_desc);
    vector_distruge(sd);

    Repo *r_sort = repo_creeaza();
    Service *s_sort = service_creeaza(r_sort);
    service_adauga(s_sort, 5, 500.0, "intrare", "E");
    service_adauga(s_sort, 2, 100.0, "intrare", "B");
    service_adauga(s_sort, 4, 300.0, "intrare", "D");
    service_adauga(s_sort, 1, 50.0, "intrare", "A");
    service_adauga(s_sort, 3, 200.0, "intrare", "C");

    Vector *sa_sort = service_sorteaza_suma_asc(s_sort);
    assert(sa_sort != NULL);
    assert(vector_lungime(sa_sort) == 5);
    assert(((Tranzactie *)vector_get(sa_sort, 0))->suma == 50.0);
    vector_distruge(sa_sort);
    service_distruge(s_sort);
    repo_distruge(r_sort);

    Vector *za = service_sorteaza_zi_asc(s);
    int ok_zi_asc = 1;
    n = vector_lungime(za);
    for (i = 0; i < n - 1; i++) {
        int a = ((Tranzactie *)vector_get(za, i))->zi;
        int b = ((Tranzactie *)vector_get(za, i+1))->zi;
        if (a > b) { ok_zi_asc = 0; break; }
    }
    assert(ok_zi_asc);
    vector_distruge(za);

    Vector *zd = service_sorteaza_zi_desc(s);
    int ok_zi_desc = 1;
    n = vector_lungime(zd);
    for (i = 0; i < n - 1; i++) {
        int a = ((Tranzactie *)vector_get(zd, i))->zi;
        int b = ((Tranzactie *)vector_get(zd, i+1))->zi;
        if (a < b) { ok_zi_desc = 0; break; }
    }
    assert(ok_zi_desc);
    vector_distruge(zd);

    Vector *toate = service_get_toate(s);
    assert(toate != NULL);
    assert(vector_lungime(toate) == service_contor(s));

    service_distruge(NULL);
    assert(1);

    service_distruge(s);
    repo_distruge(r);

    printf("Rulez teste UNDO...\n");

    Repo    *r_u = repo_creeaza();
    Service *s_u = service_creeaza(r_u);
    assert(s_u != NULL);

    assert(service_undo(NULL) == -1);
    assert(service_undo(s_u) == -2);
    assert(service_contor(s_u) == 0);

    service_adauga(s_u, 5, 100.0, "intrare", "Salariu");
    service_adauga(s_u, 10, 200.0, "iesire", "Chirie");
    assert(service_contor(s_u) == 2);
    assert(service_undo(s_u) == 1);
    assert(service_contor(s_u) == 1);
    assert(service_undo(s_u) == 1);
    assert(service_contor(s_u) == 0);

    service_adauga(s_u, 5, 100.0, "intrare", "A");
    service_adauga(s_u, 10, 200.0, "intrare", "B");
    assert(service_undo(s_u) == 1);
    assert(service_contor(s_u) == 1);
    Tranzactie *t = repo_gaseste_dupa_id(r_u, 1);
    assert(t != NULL && t->suma == 100.0);

    service_adauga(s_u, 15, 300.0, "intrare", "C");
    assert(service_contor(s_u) == 2);
    assert(service_undo(s_u) == 1);
    assert(service_contor(s_u) == 1);

    service_adauga(s_u, 20, 400.0, "intrare", "D");
    service_adauga(s_u, 25, 500.0, "intrare", "E");
    assert(service_contor(s_u) == 3);
    assert(service_undo(s_u) == 1);
    assert(service_contor(s_u) == 2);
    assert(service_undo(s_u) == 1);
    assert(service_contor(s_u) == 1);

    service_distruge(s_u);
    repo_distruge(r_u);
}

/* ================================================================
 * RUNNER TESTE
 * ================================================================ */
void run_all_tests(void)
{
    printf("\n--- START SUITE DE TESTE TDD (ASSERT) ---\n");

    test_tranzactie();
    test_vector();
    test_vv();
    test_repo();
    test_service();

    printf("--- TOATE TESTELE AU TRECUT CU SUCCES! ---\n\n");
}

int main(void)
{
    run_all_tests();
    return 0;
}
