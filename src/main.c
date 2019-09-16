#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"
#include "../include/utils.h"

int main(int argc, char* argv[]){

    automate a = creer_automate(32, 16, 2);

    generer_automate(a, 32, 30, "00000000000000000000000000000001\0");

    supprimer_automate(a);

    return EXIT_SUCCESS;
}