#include <stdio.h>
#include <stdlib.h>

#include "../include/affichage.h"
#include "../include/automate.h"
#include "../include/regles.h"
#include "../include/utils.h"

int main(int argc, char* argv[]){

    unsigned int dimension_max = 240;
    unsigned int nb_iterations = 1000;

    automate a = creer_automate(dimension_max, nb_iterations, 3);

    //somme = 0013100132 
    
    //binaire = 00011110

    cel** tableau = generer_automate(a, "0123000001", &regle_somme, "000000000000000000000000000000000000000000000000000000000000111100000011100000000001100000000110000000000000000000010000000000000000000000000000000000000000001111000000000000000000001110000000000000000000000010000011000000000000000000000000\0", &afficher_cellule_somme);

    //affichage_automate_pgm(tableau, dimension_max, nb_iterations);
    
    //lire_fichier_automate();

    afficher_automate(a, &afficher_automate_pgm);

    supprimer_automate(&a);

    return EXIT_SUCCESS;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000