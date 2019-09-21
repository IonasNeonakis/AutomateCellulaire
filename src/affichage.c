#include <stdio.h>
#include <stdlib.h>

#include "../include/affichage.h"

void afficher_cellule_binaire(int etat){
    char car;
    if(etat == 0){
        car = ' ';
    }else{
        car = 'X';
    }
    printf("%c", car);
}

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

char afficher_cellule_image(int etat){

}

void afficher_ligne(cel* ligne,unsigned int dimensions_max, void (*affichage_cellule) (int)){
    for(unsigned int i = 0; i < dimensions_max; i++){
        cel x = ligne[i];
        afficher_cellule(x, affichage_cellule);
    }
}

void afficher_automate_console(automate automate_cellulaire){
    char* regle = get_regle(automate_cellulaire);
    unsigned int nb_iterations_max = get_nb_iterations_max(automate_cellulaire);
    unsigned int dimension_max = get_dimension_max(automate_cellulaire);
    cel** configuration_actuelle = get_configuration_actuelle(automate_cellulaire);
    void* affichage_regle = get_affichage_regle(automate_cellulaire);

    printf("Règle           : %s\n", regle);
    printf("Règle binaire   : %s\n", regle);
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