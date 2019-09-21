#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"
#include "../include/utils.h"

int regle_somme(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = e_cg + e_cm + e_cd;
    return regle[x] - 48;
}

int regle_binaire(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = conversion_binaire_decimal(e_cg, e_cm, e_cd);
    return regle[x] - 48;
}

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

void creer_image_automate(cel** cellules, unsigned int dimension_max, unsigned int nb_iterations){
    FILE* image = fopen("out/automate.ppm", "w");
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

int main(int argc, char* argv[]){

    unsigned int dimension_max = 240;
    unsigned int nb_iterations = 1000;

    automate a = creer_automate(dimension_max, nb_iterations, 3);

    //somme = 0013100132 
    //binaire = 00011110

    cel** tableau = generer_automate(a, "0123000001", &regle_somme, "000000000000000000000000000000000000000000000000000000000000111100000011100000000001100000000110000000000000000000010000000000000000000000000000000000000000001111000000000000000000001110000000000000000000000010000011000000000000000000000000\0");

    creer_image_automate(tableau, dimension_max, nb_iterations);
    //lire_fichier_automate();
    afficher_automate(a, &afficher_cellule_somme);

    //supprimer_automate(&a);

    return EXIT_SUCCESS;
}

//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000