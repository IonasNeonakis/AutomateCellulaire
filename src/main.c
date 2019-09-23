#include <stdio.h>
#include <stdlib.h>

#include "../include/affichage.h"
#include "../include/automate.h"
#include "../include/regles.h"
#include "../include/utils.h"

int main(int argc, char* argv[]){

    unsigned int dimension_max = 32;
    unsigned int nb_iterations = 16;
    //char config_initiale[241] = "000011110001001110000001100000000001111100000000000000000000111100000011100000000001100000000110000000000000000000010000000000111100000000001111111110000000001111000000000000000000001110000000000000000000000010000011000000000000000000000000\0";
    char config_initiale[32]="0000000000000000000000000000000\0";
    automate a = creer_automate(dimension_max, nb_iterations, 2);

    //somme = 0013100132 
    
    //binaire = 00011110

    //cel** tableau = generer_automate(a, "0123000001", &regle_somme, config_initiale, &afficher_cellule_somme);
    set_regle(a, "00011110");
    
    set_type_regle(a,&regle_binaire);

    set_configuration_initiale(a, "00000000000000001000000000000000");
    

    set_affichage_regle(a,&afficher_cellule_binaire);
    
    set_affichage(a,&afficher_automate_console);
    //printf("je suis là\n");

    cel** tableau = generer_automate(a);
    

    //affichage_automate_pgm(tableau, dimension_max, nb_iterations);
    //automate a;
    //a = lire_fichier_automate();

    //afficher_automate(a, &afficher_automate_console);
    
    
    afficher_automate(a);


    supprimer_automate(&a);

    return EXIT_SUCCESS;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000