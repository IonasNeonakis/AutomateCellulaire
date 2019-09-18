#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"
#include "../include/utils.h"

int regle_somme(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = e_cg + e_cm + e_cd;
    return regle[strlen(regle) - 1 - x] - 48;
}

int regle_binaire(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = conversion_binaire_decimal(e_cg, e_cm, e_cd);
    return regle[strlen(regle) - 1 - x] - 48;
}

int main(int argc, char* argv[]){

    automate a = creer_automate(31, 16, 2);

    //somme = 0013100132
    //binaire = 00011110
    generer_automate(a, "0013100132", &regle_somme, "0000000000000001000000000000000\0");

    afficher_automate(a);

    supprimer_automate(&a);

    return EXIT_SUCCESS;
}