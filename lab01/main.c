/*
Calculeaza o valoare aproximativa a radacinii patrate a unui numar real pozitiv, cu o precizie data.
*/
#include <stdio.h>

typedef struct {
    double precision;
} Configuration;


/**
 * Calculeaza o valoare aproximativa a sqrt(number),
 * cu o precizie data.
 * 
 * @param number numar real, numarul pentru care se calculeaza radicalul
 * @param precision precizia dorita
 * @return o valoare reala aproximativa a radical din number, sau -1 daca `number` este negativ
 */
double radical(double number, double precision){
    if (number < 0) {
        return -1; // semnalizam o eroare pentru numere negative
    }
    else if (number == 0) { // caz special pentru 0
        return 0; // sqrt(0) este 0
    }

    double guess = number / 2.0; // o ghicire initiala, jumatatea numarului
    double delta; // diferenta dintre guess^2 si number

    // diferenta dintre guess si valoarea reala a radacinii patrate
    // trebuie sa apartina de intervalul [-precizie, precizie]
    do {

        // guess_nou = media aritmetica dintre guess si number/guess
        guess = (guess + number / guess) / 2.0; // formula lui Heron pentru imbunatatirea ghicirii

        // calculam cat de departe este guess de sqrt(number)
        delta = guess * guess - number;

    } while (delta > precision || delta < -precision);

    return guess; // returnam aproximarea pentru sqrt(number)
}


/**
 * Printarea meniului de optiuni pentru utilizator.
 * @param config Configuration structura de configurare care poate contine setari pentru meniu (de exemplu, precizia curenta)
 */
void print_menu(Configuration config) {
    printf("\n=== Meniu ===\n");
    printf("Precizia curenta: %f\n\n", config.precision);
    printf("1. Calculeaza radicalul unui numar\n");
    printf("2. Seteaza precizia\n");
    printf("0. Iesire\n");
    printf("Alege o optiune: ");
}

/**
 * Citirea optiunii alese de utilizator.
 * @return optiunea aleasa de utilizator (un numar intreg)
 */
int get_user_choice() {
    int choice;
    scanf("%d", &choice);
    return choice;
}


/**
 * Setter pt. precizie
 * @param config structura de configurare care contine setarile curente
 * @param new_precision noua valoare a preciziei care trebuie setata
 */
void set_precision(Configuration *config, double new_precision) {
    config->precision = new_precision;
}



int main() {

    Configuration config;
    config.precision = 0.00001; // setam o precizie default


    while (1)
    {
        print_menu(config);
        int choice = get_user_choice();

        switch (choice) {
            case 1: {
                printf("Introduceti un numar real pozitiv: ");
                double number;
                scanf("%lf", &number);
                double result = radical(number, config.precision);
                if (result == -1) {
                    printf("Eroare: numarul trebuie sa fie pozitiv!\n");
                } else {
                    printf("sqrt(%f) = %.5f\n", number, result);
                }
                break;
            }
            case 2: {
                printf("Introduceti noua precizie (ex: 0.00001): ");
                double new_precision;
                scanf("%lf", &new_precision);
                if (new_precision <= 0) {
                    printf("Eroare: precizia trebuie sa fie un numar pozitiv!\n");
                } else {
                    set_precision(&config, new_precision);
                    printf("Precizia a fost actualizata la %f\n", config.precision);
                }
                break;
            }
            case 0: {
                printf("La revedere!\n");
                return 0; // iesim din program
            }
            default: {
                printf("Optiune invalida!\n");
                break;
            }
        }
    }

    return 0;
}