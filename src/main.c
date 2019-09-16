#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"
#include "../include/utils.h"

int main(int argc, char* argv[]){

    automate a = creer_automate(32, 16, 2);
    
    char* nombre_binaire = conversion_decimal_binaire(256);

    free(nombre_binaire);
    supprimer_automate(a);

    return EXIT_SUCCESS;
}