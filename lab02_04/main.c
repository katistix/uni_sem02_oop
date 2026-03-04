/*
4. Inchiriere masini
Creati o aplicatie pentru o firma de inchirieri auto. Fiecare masina are un numar de inmatriculare, 
model si categorie (mini, sport, suv, etc). 
Aplicatia permite:
a) adaugare de masini
b) actualizare masina existenta
c) inchiriere masina/returnare masina
d) Vizualizare masini dupa un criteru dat (categorie, model)
e) Permite sortarea masinilor dupa: model sau categorie (crescator/descrescator)

*/


#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char nr_matricol[7]; // sir static, toate numerele matricole o sa fie de forma "AA12ABC"
	char* model; // sir dinamic de caractere pt modelul masinii
	char* categorie; // sir dinamic de caractere pt categoria masinii
} Masina;

typedef struct {
	Masina* masini;
	int capacity; // capacitatea colectiei
	int count; // cate masini sunt in colectie
} ColectieMasini;

void initialize_colectie(ColectieMasini *colectie){
	if (colectie == NULL) return; // ne asiguram ca nu incercam sa accesam un null pointer

	colectie->capacity = 10; // capacitatea initiala a colectiei de masini
	colectie->count = 0; // initial nu avem nicio masina in colectie
	// alocam memorie pentru capacitatea initiala a colectiei
	colectie->masini = (Masina*)malloc(colectie->capacity*sizeof(Masina));
}

void add(ColectieMasini *colectie, Masina masina_noua){
	if (colectie == NULL) return;


	// daca nu incape, crestem capacitatea
	if (colectie->count == colectie->capacity){
		int new_capacity = colectie->capacity * 2; // dublam capacitatea
		// realocam memorie in functie de noua capacitate
		Masina* temp = realloc(colectie->masini, new_capacity * sizeof(Masina));
		if (temp){
			colectie->masini = temp;
			colectie->capacity = new_capacity;
		}
	}

	// inseram noua masina
	colectie->masini[colectie->count] = masina_noua;
	colectie->count++;
}

int main(){
	int capacity = 10; // incepem cu o capacitate mica de masini
	// alocam memorie pentru colectia de masini
	Masina* masini = (Masina*)malloc(capacity*sizeof(Masina));
	ColectieMasini colectie;
	initialize_colectie(&colectie);

	// 
	
}
