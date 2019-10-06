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
 * - La lecture depuis un fichier
 * - La lecture depuis les arguments
 * - L'affichage du manuel d'utilisation
 * - Ou la lecture runtime si aucun argument n'est passé en entré
 * On affiche ensuite l'automate puis on libère tous les espaces alloués
 */
int main(int argc, char* argv[]){
    
    // On crée un automate vide pour pouvoir accueillir la règle ainsi que la fonction d'affichage personnalisée
    automate a = creer_automate();
    
    // On crée la règle personnalisée
    regle r = creer_regle();

    // On définit le pointeur vers la fonction de transition pour là règle
    set_type_regle(r, &regle_ionas); // A MODIFIER SI BESOIN POUR DEFINIR LA REGLE DE TRANSITION DE L'AUTOMATE PERSONNALISÉ)

    // On définit la taille de la règle
    set_taille_regle(r, 9); // A MODIFIER SI BESOIN POUR DEFINIR LA TAILLE DE LA REGLE PERSONNALISÉ

    // On associe cette règle à l'automate crée plus haut
    set_regle_automate(a, r);

    // On définit une fonction d'affichage personnalisée pour l'automate
    set_affichage(a, &afficher_automate_console_ionas); // A MODIFIER SI BESOIN POUR DEFINIR L'AFFICHAGE DE L'AUTOMATE PERSONNALISÉ


    if(argc > 1){
        char* argument = argv[1];
        if(argc == 3 && (!strcmp(argument, "-f") || !strcmp(argument, "--file"))){

            lire_fichier_automate(a, argv[2]); // On effectue une lecture par fichier

        }else if((argc == 8) && (!strcmp(argument, "-a") || !strcmp(argument, "--args"))){

            process_args(a, argc, argv); // On effectue une lecture par argument de programme

        }else if(argc == 2 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "h"))){

            manuel(); // On affiche le manuel
            supprimer_regle(&r);
            exit(EXIT_SUCCESS);

        }else{

            printf("Erreur du nombre d'arguments. Arrêt du programme !\n");
            exit(EXIT_FAILURE);

        }
    }else if(argc == 1){

        lecture_runtime_automate(a); // On effectue une lecture runtime

    }

    afficher_automate(a);
    supprimer_automate(&a);
 
    return EXIT_SUCCESS;
}
