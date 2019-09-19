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
        case 0:
            car = ' ';
            break;
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
            car = 'Y';
            break;
    }
    printf("%c", car);
}

void creer_image_automate(cel** cellules){
    FILE* image = fopen("out/automate.pgm", "w");
    fprintf(image, "P2\n");
    fprintf(image, "31 16\n");
    fprintf(image, "%d\n", 15);
    for(unsigned int i = 0; i < 16; i++){
        for(unsigned int j = 0; j < 31; j++){
            fprintf(image, "%d ", get_etat(cellules[i][j]) == 1 ? 15 : 0);
        }
        fprintf(image, "\n");
    }
    fclose(image);
}

int main(int argc, char* argv[]){

    automate a = creer_automate(31, 16, 2);

    //somme = 0013100132
    //binaire = 00011110
    cel** tableau = generer_automate(a, "00011110", &regle_binaire, "0000000000000001000000000000000\0");

    creer_image_automate(tableau);

    afficher_automate(a, &afficher_cellule_binaire);

    supprimer_automate(&a);

    return EXIT_SUCCESS;
}