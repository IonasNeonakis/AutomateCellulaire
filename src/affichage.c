/**
 * \file affichage.c
 * \brief Ce fichier s'occupe de l'affichage des cellules ainsi que de la sortie de l'affichage.
 * \author Ionas Samir
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/affichage.h"


/**
 * \fn void afficher_cellule_binaire(int etat)
 * \brief Fonction qui affiche un X à la place d'un etat à 1 et un espace à la place d'un état à 0
 *        Elle est utilisée pour l'affichage de la règle binaire  
 * \author Ionas
 * \param etat est l'état de la cellule à afficher.
 */

void afficher_cellule_binaire(int etat){
    char car;
    if(etat == 0){
        car = ' ';
    }else{
        car = 'X';
    }
    printf("%c", car);
}


/**
 * \fn void afficher_cellule_somme(int etat)
 * \brief Fonction qui affiche un le nombre de l'état et un espace si le nombre de l'état est 0. Elle est utilisée
 *        Elle est utilisée pour l'affichage de la regle Somme  
 * \author Ionas
 * \param etat est l'état de la cellule à afficher.
 */
void afficher_cellule_somme(int etat){
    char car;
    switch (etat){
        case 1:
            car = '1';
            break;
        case 2:
            car = '2';
            break;
        case 3:
            car = '3';
            break;
        default:
            car = ' ';
            break;
    }
    printf("%c", car);
}

/**
 * \fn void afficher_ligne(cel* ligne,unsigned int dimensions_max, void (*affichage_cellule) (int))
 * \brief Fonction qui affiche la ligne compléte d'une cellule  
 * \author Ionas
 * \param ligne est la ligne à afficher.
 * \param dimensions_max est la dimension max soit la longueur de la ligne
 * \param affichage_cellule est la fonction d'affichage d'une cellule
 */

void afficher_ligne(cel* ligne,unsigned int dimensions_max, void (*affichage_cellule) (int)){
    for(unsigned int i = 0; i < dimensions_max; i++){
        cel x = ligne[i];
        afficher_cellule(x, affichage_cellule);
    }
}
/**
 * \fn void afficher_automate_console(automate automate_cellulaire)
 * \brief Fonction qui affiche un automate sur la console  
 * \author Ionas Samir
 * \param automate_cellulaire est l'automate à afficher.
 */

void afficher_automate_console(automate automate_cellulaire){
    regle r = get_regle_automate(automate_cellulaire);
    char* regle = get_regle(r);
    unsigned int nb_iterations_max = get_nb_iterations_max(automate_cellulaire);
    unsigned int dimension_max = get_dimension_max(automate_cellulaire);
    cel** configuration_actuelle = get_configuration_actuelle(automate_cellulaire);
    void (*affichage_regle)(int) = get_affichage_regle(r);
    
    printf("Règle           : %s\n", regle);
    if(affichage_regle == &afficher_cellule_binaire){
        int regle_int = conversion_regle_binaire_decimal(regle);
        printf("Règle Wolfram   : %d\n", regle_int);
    }
    printf("Itérations      : %u\n", nb_iterations_max);
    printf("Dimensions Max. : %u\n\n", dimension_max);

    for(unsigned int i = 0 ; i < nb_iterations_max; i++){
        if (i < 10)
            printf("|%u | ", i);
        else
            printf("|%u| ", i);

        afficher_ligne(configuration_actuelle[(int)i], dimension_max, affichage_regle);

        printf("\n");
    }
}

/**
 * \fn void afficher_automate_pgm(automate automate_cellulaire)
 * \brief Fonction qui affiche un automate sous la forme d'une image ppm, elle est de couleur si la regle est de type Somme 
 * \author Ionas 
 * \param automate_cellulaire est l'automate à afficher.
 */

void afficher_automate_pgm(automate automate_cellulaire){
    FILE* image;
    if ((image = fopen("./out/automate.ppm", "w")) != NULL)
        {
            unsigned int dimension_max = get_dimension_max(automate_cellulaire);
            unsigned int nb_iterations = get_nb_iterations_max(automate_cellulaire);
            cel** cellules = get_configuration_actuelle(automate_cellulaire);
            fprintf(image, "P3\n");
            fprintf(image, "%d ", dimension_max);
            fprintf(image, "%d\n", nb_iterations);
            fprintf(image, "%d\n", 255);
            for(unsigned int i = 0; i < nb_iterations; i++){
                for(unsigned int j = 0; j < dimension_max; j++){
                    int etat = get_etat(cellules[i][j]);
                    switch(etat){
                        case 0: {
                            fprintf(image, "%d ", 255);
                            fprintf(image, "%d ", 255);
                            fprintf(image, "%d ", 255);
                            break;
                        } 
                        case 1: {
                            fprintf(image, "%d ", 0);
                            fprintf(image, "%d ", 0);
                            fprintf(image, "%d ", 0);
                            break;
                        } 
                        case 2: {
                            fprintf(image, "%d ", 0);
                            fprintf(image, "%d ", 255);
                            fprintf(image, "%d ", 0);
                            break;
                        } 
                        case 3: {
                            fprintf(image, "%d ", 0);
                            fprintf(image, "%d ", 0);
                            fprintf(image, "%d ", 255);
                            break;
                        } 
                    }
                }
                fprintf(image, "\n");
            }
            fclose(image);
        }
    else
        perror("fopen");
}