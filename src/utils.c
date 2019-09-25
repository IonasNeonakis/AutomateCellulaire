#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

int conversion_binaire_decimal(int etat_cel1, int etat_cel2, int etat_cel3){
    return ((etat_cel1 * 4) + (etat_cel2 * 2) + etat_cel3); 
}

char* conversion_decimal_binaire(int n){
    int taille = (int)floor(log2(n));
    char* nombre_binaire = (char*) calloc (8, sizeof(char) * 8);
    int i = 0; 
    while (n > 0) {
        nombre_binaire[taille - i] = n % 2 + '0'; 
        n = n / 2; 
        i++; 
    }
    char* remplir = (char*) calloc (8, sizeof(char) * 8 + 1);
    for(int i = 0; i < 3; i++){
        remplir[i] = '0';
    }
    remplir[7] = '\0';
    nombre_binaire[taille + 1] = '\0';
    strcat(remplir, nombre_binaire);
    free(nombre_binaire);
    nombre_binaire = NULL;
    return remplir;
}

int conversion_char_int(char * s){
    int total =0 ;
    for (int i =0;i<(int) strlen(s);i++){
        total=total*10+s[i]-48;
    }
    return total;
}

bool est_un_int(char *s){
    for (int i =0;i<(int) strlen(s);i++){
        if(s[i]<48 || s[i]>57)
            return false;
    }
    return true;
}

bool est_de_longueur(char *s,int n){
    if((int)strlen(s)!=n){
        return false;
    }
    return true;
}

bool est_regle_binaire(char *s){
    for (int i =0;i<(int) strlen(s);i++){
        if(s[i]!=48 && s[i]!=49){
            return false;
        }
    }
    return true;

}

bool est_regle_somme(char* s){
    size_t taille = strlen(s);
    for (unsigned int i = 0; i < taille; i++){
        if(s[i] != 48 && s[i] != 49 && s[i] != 50 && s[i] != 51)
            return false;
    }
    return true;
}

bool est_regle_correcte(char* s, unsigned int nb_etats){
    size_t taille = strlen(s);
    for(unsigned int i = 0; i < taille; i++){
        if(s[i] < 48 || s[i] > 48 + ((int)nb_etats) - 1){
            return false;
        }
    }
    return true;
}