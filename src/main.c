#include <stdio.h>
#include <stdlib.h>

#include "../include/affichage.h"
#include "../include/automate.h"
#include "../include/regle.h"
#include "../include/utils.h"

int main(int argc, char* argv[]){
    
    automate a;
    
    regle r = creer_regle();
    set_type_regle(r, &regle_binaire);
    set_taille_regle(r, 8);
    set_affichage_regle(r, &afficher_cellule_binaire);

    if(argc > 1){
        char* argument = argv[1];
        if(argc == 3 && (!strcmp(argument, "-f") || !strcmp(argument, "--file"))){
            //printf("%s",argv[2]);
            a = lire_fichier_automate(r, argv[2]); //on lit par fichier
        }else if((argc == 9 || argc==8) && !strcmp(argument, "-a")){
            a = process_args(r, argc, argv); //on fait une lecture par arguments
        }else{
            //nombre d'arguments incorrect
        }
    }else if(argc == 1){
        a = lecture_runtime_automate(r); //on fait une lecture runtime
    }

    afficher_automate(a);
    supprimer_automate(&a);

    //unsigned int dimension_max = 32;
    //unsigned int nb_iterations = 16;
    //char config_initiale[241] = "000011110001001110000001100000000001111100000000000000000000111100000011100000000001100000000110000000000000000000010000000000111100000000001111111110000000001111000000000000000000001110000000000000000000000010000011000000000000000000000000\0";
    //char config_initiale[33]="00000000000000001000000000000000\0";
    //automate a = creer_automate(dimension_max, nb_iterations, 3);

    //somme = 0013100132 
    
    //binaire = 00011110

    //cel** tableau = generer_automate(a, "0123000001", &regle_somme, config_initiale, &afficher_cellule_somme);
    
    // set_regle(a, "2013101132");

    // set_type_regle(a,&regle_somme);
    // 

    // set_configuration_initiale(a, config_initiale);
    
    // set_affichage_regle(a, &afficher_cellule_somme);
    
    // set_affichage(a, &afficher_automate_console);

    // cel** tableau = generer_automate(a);

    //affichage_automate_pgm(tableau, dimension_max, nb_iterations);

    //afficher_automate(a, &afficher_automate_console);

    return EXIT_SUCCESS;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000