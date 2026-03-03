/*
Calculeaza o valoare aproximativa a radacinii patrate a unui numar real pozitiv, cu o precizie data.
*/
#include <stdio.h>

int main() {
    // double number, precision, guess, difference;
    double number, guess, delta, precizie;

    // citire
    printf("Introduceti un numar real pozitiv: ");
    scanf("%lf", &number);
    printf("Introduceti precizia dorita: ");
    scanf("%lf", &precizie);

    if (number < 0) {
        printf("numarul trebuie sa fie pozitiv.\n");
        return 1;
    }
    else if (number == 0) {
        printf("sqrt(0) = 0\n");
        return 0;
    }


    // incercam o ghicire naiva pentru sqrt(number), jumatatea numarului
    guess = number / 2.0; 


    // diferenta dintre guess si valoarea reala a radacinii patrate
    // trebuie sa apartina de intervalul [-precizie, precizie]
    do {

        // guess_nou = media aritmetica dintre guess si number/guess
        guess = (guess + number / guess) / 2.0; // formula lui Heron pentru imbunatatirea ghicirii

        // calculam cat de departe este guess de sqrt(number)
        delta = guess * guess - number;

    } while (delta > precizie || delta < -precizie);
    



    // // Afisarea rezultatului
    printf("sqrt(%f) = %.5f", number, guess);

    return 0;
}