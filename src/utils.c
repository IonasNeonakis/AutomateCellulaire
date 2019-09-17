#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

int conversion_binaire_decimal(int etat_cel1, int etat_cel2, int etat_cel3){
    return ((etat_cel1 * 4) + (etat_cel2 * 2) + etat_cel3); 
}

char* conversion_decimal_binaire(int n){
    int taille = (int)floor(log2(n));
    char* nombre_binaire = (char*) malloc (sizeof(char) * 8);
    int i = 0; 
    while (n > 0) {
        nombre_binaire[taille - i] = n % 2 + '0'; 
        n = n / 2; 
        i++; 
    }
    char* remplir = (char*) malloc (sizeof(char) * (8 - strlen(nombre_binaire) + 1));
    for(int i = 0; i < (int)(8 - strlen(nombre_binaire)); i++){
        remplir[i] = '0';
    }
    remplir[(int)strlen(remplir)] = '\0';
    strcat(remplir, nombre_binaire);
    nombre_binaire[taille + 1] = '\0';
    free(nombre_binaire);
    nombre_binaire = NULL;
    return remplir;
}