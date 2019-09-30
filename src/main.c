/**
 * \file main.c
 * \brief Ce fichier contient le main et lance le programme en fonction des arguments passés lors de l'éxecution
 * \author Ionas Samir
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"
#include "../include/affichage.h"
#include "../include/io.h"
#include "../include/regle.h"
#include "../include/utils.h"

/**
 * \fn int main(int argc, char* argv[])
 * \brief Fonction main qui crée un automate. On lui affecte la regle, la taille de regle et son affichage si on veut une règle particulière.
 * \author Ionas Samir
 * \param automate_cellulaire est l'automate à afficher.
 * 
 * En fonction des arguments passés lors de l'éxecution (-f ou --file | -a ou --args | --help) on effectue une opération particulière, telle que respectivement
 * -La lecture depuis un fichier
 * -La lecture depuis les arguments
 * -L'affichage du manuel d'utilisation
 * -Ou la lecture runtime si aucun argument n'est passé en entré
 * On affiche ensuite l'automate puis on libère tous les espaces alloués
 */
int main(int argc, char* argv[]){
    
    automate a = creer_automate();
    
    regle r = creer_regle();
    set_type_regle(r, &regle_binaire);
    set_taille_regle(r, 8);
    // set_affichage(a, &afficher_automate_console_binaire);
    set_regle_automate(a, r);
    set_affichage(a, &afficher_automate_console_binaire);

    if(argc > 1){
        char* argument = argv[1];
        if(argc == 3 && (!strcmp(argument, "-f") || !strcmp(argument, "--file"))){
            //printf("%s",argv[2]);
            a = lire_fichier_automate(r, argv[2]); //on lit par fichier
        }else if((argc == 9 || argc==8) && (!strcmp(argument, "-a") || !strcmp(argument, "--args"))){
            a = process_args(r, argc, argv); //on fait une lecture par arguments
        }else if(argc == 2 && !strcmp(argv[1], "--help")){
            manuel();
            supprimer_regle(&r);
            //supprimer_automate(&a);
            exit(EXIT_SUCCESS);
        }else{
            printf("Erreur du nombre d'arguments. Arrêt du programme ! \n");
            exit(1);
            //nombre d'arguments incorrect
        }
    }else if(argc == 1){
        lecture_runtime_automate(a, r); //on fait une lecture runtime
    }

    afficher_automate(a);
    supprimer_automate(&a);
 
    return EXIT_SUCCESS;
}
