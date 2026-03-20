#include <stdlib.h>
#include <stdio.h>


int main() {

    int n = 5;

    // alocam memoria
    char **brad = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++)
    {
        brad[i] = malloc((2*i+1)*sizeof(char));
    }


    // initializare
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2*i+1; j++)
        {
            brad[i][j]='*';
        }
    }


    // printare
    for (int i = 0; i < n; i++)
    {
        // for (int j = 0; j < n-i-1; j++){
        //     printf(" ");
        // }
        // for (int j = 0; j < 2*i+1; j++)
        // {
        //     printf("%c", brad[i][j]);
        // }
        // printf("\n");
        printf("%*s\n", n+i, brad[i]);
    }
    

    // eliberam memoria
    for (int i = 0; i < n; i++)
    {
        free(brad[i]);
    }
    free(brad);
    
    return 0;
}