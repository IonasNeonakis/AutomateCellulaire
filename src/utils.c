#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

int conversion_binaire_decimal(int etat_cel1, int etat_cel2, int etat_cel3){
    return ((etat_cel1 * 4) + (etat_cel2 * 2) + etat_cel3); 
}

int conversion_regle_binaire_decimal(char* regle){
    size_t taille = strlen(regle);
    int res = 0;
    for(int i = taille - 1; i >= 0; i--){
        int n = regle[i] - 48;
        if(n == 1){
            res += pow(2, taille - i - 1);
        }
    }
    return res;
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

void manuel(){
    printf("Bienvenue dans le manuel !\n");
    printf("Ce programme vous permet de générer un automate cellulaire en fonction de plusieurs paramètres.\n");
    printf("Afin de correctement générer un automate, plusieurs options sont disponibles : \n\n");
    printf("Il est tout d'abord possible de générer l'automate cellulaire en utilisant un fichier de configuration.\n");
    printf("Ce fichier doit être placer dans le dossier 'cfg' et doit absolument respecter les modèles déjà présent dans ce dossier.\n");
    printf("NOTE : Le nombre d'état doit ne doit être précisé dans le cas unique où vous créez votre propre règle. Il n'est donc pas nécessaire de préciser ce nombre lors de l'utilisation de la règle de Wolfram ou Somme\n\n");
    printf("Il est également possible de générer un automate en passant des arguments directement au programme donc voici l'ordre :\n\n");
    printf("NOMBRE_ITERATIONS  DIMENSION_MAX  CONFIGURATION_INITIALE  REGLE  TYPE_REGLE  TYPE_AFFICHAGE  [NB_ETATS]\n\n");
    printf("- Le nombre d'itération doit etre un entier positif\n");
    printf("- La dimension max doit être un entier positif\n");
    printf("- La taille de la configuration initiale doit être égale à la dimension max, et ne doit comporter que des chiffres compris entre 0 et le nombre d'états possibles\n");
    printf("- La règle somme est une succession de 10 entier compris entre 0 et 3\n");
    printf("- La règle de Wolfram est un entier compris entre 0 et 255\n");
    printf("NOTE : Dans le cas d'une règle personnalisée, vous devrez concevoir son implémentation ainsi que sa règle d'affichage dans le code\n");
    printf("- Type règle est 0 pour une règle de Wolfram, 1 pour une règle somme, 2 pour une règle personnalisée\n");
    printf("- Type affichage est 0 pour un affichage dans la console, 1 pour la génération d'une image de l'automate\n");
    printf("Nombre d'états corresponds aux états possibles pour une cellule, ce chiffre, positif, ne doit être précisé seulement dans le cas de l'utilisation d'une règle personnalisée\n\n");
    printf("Enfin, il est possible de générer un automate en utilisant la lecture runtime, c'est à dire pendant l'exécution du programme, les règles à respecter sont identiques à celles cîtées plus haut.\n");
    printf("NOTE : Tant que vous ne rentrerez pas une valeur correcte vérifiant chacunes de ces règles, le programme vous redemandera la valeur.\n\n");
    printf("Merci d'avoir lu ce manuel, bon courage ! :)");
}