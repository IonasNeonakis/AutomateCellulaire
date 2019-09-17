#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"
#include "../include/utils.h"

int main(int argc, char* argv[]){

    automate a = creer_automate(31, 16, 2);

    generer_automate(a, 31, 30, "0000000000000001000000000000000\0");

    afficher_automate(a);

    supprimer_automate(&a);

    return EXIT_SUCCESS;
}