#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

int conversion_binaire_decimal(int etat_cel1, int etat_cel2, int etat_cel3){
    return ((etat_cel1 * 4) + (etat_cel2 * 2) + etat_cel3); 
}

char* conversion_decimal_binaire(int n){
    const int taille = (int)floor(log2(n));
    char* nombre_binaire = (char*) malloc (sizeof(char) * taille + 2);
    int i = 0; 
    while (n > 0) {
        nombre_binaire[taille - i] = n % 2 + '0'; 
        n = n / 2; 
        i++; 
    }
    nombre_binaire[taille + 1] = '\0';
    return nombre_binaire;
}