#include <cassert>
#include <iostream>
#include <sstream>

#include "domain/Produs.h"
#include "utils/CustomVector.h"
#include "utils/ProdusComparators.h"
#include "repo/RepoProduse.h"
#include "validators/ProdusValidator.h"
#include "service/ServiceProduse.h"
#include "exceptions/RepositoryException.h"

using namespace std;

// ===== CustomVector =====

void test_custom_vector_constructor()
{
    const CustomVector<int> v;
    assert(v.get_size() == 0);
}

void test_custom_vector_add()
{
    CustomVector<int> v;
    v.add(42);
    assert(v.get_size() == 1);
    assert(v.get_by_index(0) == 42);
}

void test_custom_vector_resize()
{
    // capacity starts at 1, adding 3 elements forces resize
    CustomVector<int> v;
    v.add(1);
    v.add(2);
    v.add(3);
    assert(v.get_size() == 3);
    assert(v.get_by_index(0) == 1);
    assert(v.get_by_index(1) == 2);
    assert(v.get_by_index(2) == 3);
}

void test_custom_vector_remove()
{
    CustomVector<int> v;
    v.add(10);
    v.add(20);
    v.add(30);
    v.remove_index(1); // remove middle
    assert(v.get_size() == 2);
    assert(v.get_by_index(0) == 10);
    assert(v.get_by_index(1) == 30);
}

// ===== Produs =====

void test_produs_constructor()
{
    const Produs p(1, "nume1", "tip1", 3.14, "prod1");
    assert(p.getId() == 1);
    assert(strcmp(p.getNume(), "nume1") == 0);
    assert(strcmp(p.getTip(), "tip1") == 0);
    assert(p.getPret() == 3.14);
    assert(strcmp(p.getProducator(), "prod1") == 0);
}

void test_produs_default_constructor()
{
    const Produs p;
    assert(p.getId() == 0);
    assert(p.getPret() == 0.0);
}

void test_produs_copy_constructor()
{
    const Produs a(2, "abc", "tip", 5.0, "brand");
    const Produs b(a);
    assert(b.getId() == 2);
    assert(strcmp(b.getNume(), "abc") == 0);
    assert(strcmp(b.getTip(), "tip") == 0);
    assert(b.getPret() == 5.0);
    assert(strcmp(b.getProducator(), "brand") == 0);
    assert(b.getNume() != a.getNume()); // deep copy: different pointers
}

void test_produs_copy_assignment()
{
    const Produs a(3, "x", "y", 1.0, "z");
    Produs b(1, "old", "old", 0.0, "old");
    b = a;
    assert(b.getId() == 3);
    assert(strcmp(b.getNume(), "x") == 0);
    assert(b.getNume() != a.getNume()); // deep copy
}

void test_produs_self_assignment()
{
    Produs a(4, "self", "tip", 2.0, "brand");
    a = a; // must not crash or corrupt
    assert(a.getId() == 4);
    assert(strcmp(a.getNume(), "self") == 0);
}

void test_produs_stream_operator()
{
    const Produs p(1, "abc", "tip", 9.99, "brand");
    ostringstream oss;
    oss << p;
    const string result = oss.str();
    assert(result.find("abc") != string::npos);
    assert(result.find("brand") != string::npos);
}

// ===== ProdusComparators =====

void test_cmp_by_pret()
{
    const Produs cheap(1, "a", "t", 1.0, "p");
    const Produs expensive(2, "b", "t", 10.0, "p");
    assert(cmpByPret(cheap, expensive) == true);
    assert(cmpByPret(expensive, cheap) == false);
}

void test_cmp_by_id()
{
    const Produs low(1, "a", "t", 1.0, "p");
    const Produs high(5, "b", "t", 1.0, "p");
    assert(cmpById(low, high) == true);
    assert(cmpById(high, low) == false);
}

void test_cmp_by_name()
{
    const Produs apple(1, "apple", "t", 1.0, "p");
    const Produs banana(2, "banana", "t", 1.0, "p");
    assert(cmpByName(apple, banana) == true);
    assert(cmpByName(banana, apple) == false);
}

// ===== ValidationException =====

void test_validation_exception_single_message()
{
    const ValidationException ex("some error");
    assert(ex.getMessage() == "some error");
}

void test_validation_exception_multiple_messages()
{
    const ValidationException ex(vector<string>{"err1", "err2"});
    assert(ex.getMessage().find("err1") != string::npos);
    assert(ex.getMessage().find("err2") != string::npos);
}

// ===== ProdusValidator =====

void test_validator_valid()
{
    const Produs p(1, "name", "type", 5.0, "brand");
    ProdusValidator::validate(p); // must not throw
}

void test_validator_invalid_id()
{
    const Produs p(0, "name", "type", 5.0, "brand");
    try {
        ProdusValidator::validate(p);
        assert(false);
    } catch (const ValidationException& e) {
        assert(!e.getMessage().empty());
    }
}

void test_validator_negative_price()
{
    const Produs p(1, "name", "type", -1.0, "brand");
    try {
        ProdusValidator::validate(p);
        assert(false);
    } catch (const ValidationException& e) {
        assert(!e.getMessage().empty());
    }
}

void test_validator_empty_name()
{
    const Produs p(1, "", "type", 5.0, "brand");
    try {
        ProdusValidator::validate(p);
        assert(false);
    } catch (const ValidationException& e) {
        assert(!e.getMessage().empty());
    }
}

void test_validator_empty_type()
{
    const Produs p(1, "name", "", 5.0, "brand");
    try {
        ProdusValidator::validate(p);
        assert(false);
    } catch (const ValidationException& e) {
        assert(!e.getMessage().empty());
    }
}

void test_validator_empty_manufacturer()
{
    const Produs p(1, "name", "type", 5.0, "");
    try {
        ProdusValidator::validate(p);
        assert(false);
    } catch (const ValidationException& e) {
        assert(!e.getMessage().empty());
    }
}

void test_validator_multiple_errors()
{
    // id invalid AND price invalid — both errors in one throw
    const Produs p(-1, "name", "type", -5.0, "brand");
    try {
        ProdusValidator::validate(p);
        assert(false);
    } catch (const ValidationException& e) {
        assert(e.getMessage().find("ID") != string::npos);
    }
}

// ===== RepoProduse =====

void test_repo_add_and_get_all()
{
    RepoProduse repo;
    repo.add(Produs(1, "name", "type", 5.0, "brand"));
    assert(repo.getAll().get_size() == 1);
    assert(repo.getAll().get_by_index(0).getId() == 1);
}

void test_repo_add_duplicate_throws()
{
    RepoProduse repo;
    repo.add(Produs(1, "name", "type", 5.0, "brand"));
    try {
        repo.add(Produs(1, "other", "type", 5.0, "brand"));
        assert(false);
    } catch (const RepositoryException& e) {
        assert(!e.message.empty());
    }
}

void test_repo_sterge()
{
    RepoProduse repo;
    repo.add(Produs(1, "name", "type", 5.0, "brand"));
    repo.sterge(1);
    assert(repo.getAll().get_size() == 0);
}

void test_repo_sterge_not_found_throws()
{
    try {
        RepoProduse repo;
        repo.sterge(99);
        assert(false);
    } catch (const RepositoryException& e) {
        assert(!e.message.empty());
    }
}

void test_repo_update()
{
    RepoProduse repo;
    repo.add(Produs(1, "old", "type", 5.0, "brand"));
    repo.update(Produs(1, "new", "type", 9.0, "brand"));
    assert(strcmp(repo.getAll().get_by_index(0).getNume(), "new") == 0);
    assert(repo.getAll().get_by_index(0).getPret() == 9.0);
}

void test_repo_update_not_found_throws()
{
    try {
        const RepoProduse repo;
        repo.update(Produs(99, "name", "type", 1.0, "brand"));
        assert(false);
    } catch (const RepositoryException& e) {
        assert(!e.message.empty());
    }
}

// ===== ServiceProduse =====

void test_service_add()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "name", "type", 5.0, "brand");
    assert(srv.getAllProduse().get_size() == 1);
}

void test_service_add_invalid_throws()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    try {
        srv.add(0, "name", "type", 5.0, "brand"); // id=0 is invalid
        assert(false);
    } catch (const ValidationException& e) {
        assert(!e.getMessage().empty());
    }
}

void test_service_add_duplicate_throws()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "name", "type", 5.0, "brand");
    try {
        srv.add(1, "other", "type", 5.0, "brand");
        assert(false);
    } catch (const RepositoryException& e) {
        assert(!e.message.empty());
    }
}

void test_service_sterge()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "name", "type", 5.0, "brand");
    srv.sterge(1);
    assert(srv.getAllProduse().get_size() == 0);
}

void test_service_sterge_not_found_throws()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    try {
        srv.sterge(99);
        assert(false);
    } catch (const RepositoryException& e) {
        assert(!e.message.empty());
    }
}

void test_service_update()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "old", "type", 5.0, "brand");
    constexpr char name[] = "new";
    constexpr char tip[]  = "type";
    constexpr char prod[] = "brand";
    srv.update(1, name, tip, 9.0, prod);
    assert(strcmp(srv.getAllProduse().get_by_index(0).getNume(), "new") == 0);
}

void test_service_update_invalid_throws()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    constexpr char name[] = "x";
    constexpr char tip[]  = "t";
    constexpr char prod[] = "p";
    try {
        srv.update(-1, name, tip, 1.0, prod); // id=-1 fails validation
        assert(false);
    } catch (const ValidationException& e) {
        assert(!e.getMessage().empty());
    }
}

void test_service_get_sorted_by_price()
{
    // getSorted swaps when cmp(j, j+1) is true (i.e. j < j+1) -> result is DESCENDING
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "a", "t", 10.0, "p");
    srv.add(2, "b", "t", 30.0, "p");
    srv.add(3, "c", "t", 20.0, "p");

    const auto sorted = srv.getSorted(cmpByPret);
    assert(sorted.get_size() == 3);
    assert(sorted.get_by_index(0).getPret() >= sorted.get_by_index(1).getPret());
    assert(sorted.get_by_index(1).getPret() >= sorted.get_by_index(2).getPret());
}

void test_service_get_sorted_by_id()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(3, "c", "t", 1.0, "p");
    srv.add(1, "a", "t", 1.0, "p");
    srv.add(2, "b", "t", 1.0, "p");

    const auto sorted = srv.getSorted(cmpById);
    // descending: 3, 2, 1
    assert(sorted.get_by_index(0).getId() == 3);
    assert(sorted.get_by_index(1).getId() == 2);
    assert(sorted.get_by_index(2).getId() == 1);
}

void test_service_get_sorted_by_name()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "banana", "t", 1.0, "p");
    srv.add(2, "apple",  "t", 1.0, "p");
    srv.add(3, "cherry", "t", 1.0, "p");

    const auto sorted = srv.getSorted(cmpByName);
    // descending alphabetical: cherry, banana, apple
    assert(strcmp(sorted.get_by_index(0).getNume(), "cherry") == 0);
    assert(strcmp(sorted.get_by_index(1).getNume(), "banana") == 0);
    assert(strcmp(sorted.get_by_index(2).getNume(), "apple")  == 0);
}

void test_service_get_filtered_matches()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "a", "electronics", 100.0, "p");
    srv.add(2, "b", "food",        5.0,   "p");
    srv.add(3, "c", "electronics", 200.0, "p");

    const auto result = srv.getFiltered([](const Produs& p){
        return strcmp(p.getTip(), "electronics") == 0;
    });
    assert(result.get_size() == 2);
}

void test_service_get_filtered_empty()
{
    RepoProduse repo;
    ProdusValidator val;
    const ServiceProduse srv(repo, val);
    srv.add(1, "a", "food", 5.0, "p");

    const auto result = srv.getFiltered([](const Produs& p){
        return strcmp(p.getTip(), "electronics") == 0;
    });
    assert(result.get_size() == 0);
}

int main()
{
    cout << "running tests...\n";

    test_custom_vector_constructor();
    test_custom_vector_add();
    test_custom_vector_resize();
    test_custom_vector_remove();

    test_produs_constructor();
    test_produs_default_constructor();
    test_produs_copy_constructor();
    test_produs_copy_assignment();
    test_produs_self_assignment();
    test_produs_stream_operator();

    test_cmp_by_pret();
    test_cmp_by_id();
    test_cmp_by_name();

    test_validation_exception_single_message();
    test_validation_exception_multiple_messages();

    test_validator_valid();
    test_validator_invalid_id();
    test_validator_negative_price();
    test_validator_empty_name();
    test_validator_empty_type();
    test_validator_empty_manufacturer();
    test_validator_multiple_errors();

    test_repo_add_and_get_all();
    test_repo_add_duplicate_throws();
    test_repo_sterge();
    test_repo_sterge_not_found_throws();
    test_repo_update();
    test_repo_update_not_found_throws();

    test_service_add();
    test_service_add_invalid_throws();
    test_service_add_duplicate_throws();
    test_service_sterge();
    test_service_sterge_not_found_throws();
    test_service_update();
    test_service_update_invalid_throws();
    test_service_get_sorted_by_price();
    test_service_get_sorted_by_id();
    test_service_get_sorted_by_name();
    test_service_get_filtered_matches();
    test_service_get_filtered_empty();

    cout << "all tests passed!\n";
    return 0;
}
