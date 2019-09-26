/**
 * \file utils.c
 * \brief Ce fichier s'occupe de toutes le foctions utilitaires.
 * \author Ionas Samir
 *
 * Fonctions utilitaires tels que les conversions et les tests de types
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

/**
 * \fn int conversion_binaire_decimal(int etat_cel1, int etat_cel2, int etat_cel3)
 * \brief Cette fonction prends 3 etats en forme de int et retourne le nombre décimal de ce chiffre binaire à 3 bits.
 * \author Ionas
 * \param etat_cel1 est le premier bit
 * \param etat_cel2 est le deuxième bit
 * \param etat_cel3 est le troisième bit
 * \return Le nombre decimal de ce chiffre binaire à 3 bits.
 */

int conversion_binaire_decimal(int etat_cel1, int etat_cel2, int etat_cel3){
    return ((etat_cel1 * 4) + (etat_cel2 * 2) + etat_cel3); 
}

/**
 * \fn int conversion_regle_binaire_decimal(char* regle)
 * \brief Cette fonction prends une regle sous forme de bits et retourne l'entier correspondant.
 * \author Samir
 * \param regle est la regle en bits 
 * \return un int correspondant au bit entré en paramètres
 */

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

/**
 * \fn int conversion_regle_binaire_decimal(char* regle)
 * \brief Cette fonction prends une entier et retourne le nombre binaire correspondant.
 * \author Samir
 * \param n est l'entier à convertir
 * \return le nombre en binaire sous form d'un char*
 */

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

/**
 * \fn int conversion_char_int(char * s)
 * \brief Cette fonction prends un char* et l'entier de ce char*.
 * \author Ionas
 * \param l'int sous forme d'un char*
 * \return le nombre en int
 */

int conversion_char_int(char * s){
    int total =0 ;
    for (int i =0;i<(int) strlen(s);i++){
        total=total*10+s[i]-48;
    }
    return total;
}

/**
 * \fn bool est_un_int(char *s)
 * \brief Cette fonction vérifie qu'un char* passé en paramètres est bien un entier.
 * \author Ionas
 * \param s est le char* sur lequel on va tester s'il est entier
 * \return true si c'est un int, false sinon
 */

bool est_un_int(char *s){
    for (int i =0;i<(int) strlen(s);i++){
        if(s[i]<48 || s[i]>57)
            return false;
    }
    return true;
}

/**
 * \fn bool est_de_longueur(char *s,int n)
 * \brief Cette fonction vérifie qu'un char* passé en paramètres est de longeur n passé en paramètres.
 * \author Ionas
 * \param s est le char* sur lequel on va tester s'il est de longueur
 * \param n est l'entier à verifier si il est de la même longueur que la chaine s
 * \return true si c'est de la même taille, false sinon
 */

bool est_de_longueur(char *s,int n){
    if((int)strlen(s)!=n){
        return false;
    }
    return true;
}

/**
 * \fn bool est_regle_binaire(char *s)
 * \brief Cette fonction vérifie qu'un char* passé en paramètres est un char* composé de 0 et de 1.
 * \author Ionas
 * \param s est le char* sur lequel on va tester s'il c'est un binaire
 * \return true si c'est un char* binaire, false sinon
 */

bool est_regle_binaire(char *s){
    for (int i =0;i<(int) strlen(s);i++){
        if(s[i]!=48 && s[i]!=49){
            return false;
        }
    }
    return true;

}

/**
 * \fn bool est_regle_somme(char* s)
 * \brief Cette fonction vérifie qu'un char* passé en paramètres soit composé de 0, 1, 2 et 3.
 * \author Ionas
 * \param s est le char* sur lequel on va tester s'il c'est un type somme
 * \return true si c'est un char* de type somme, false sinon
 */

bool est_regle_somme(char* s){
    size_t taille = strlen(s);
    for (unsigned int i = 0; i < taille; i++){
        if(s[i] != 48 && s[i] != 49 && s[i] != 50 && s[i] != 51)
            return false;
    }
    return true;
}

/**
 * \fn bool est_regle_correcte(char* s, unsigned int nb_etats)
 * \brief Cette fonction vérifie qu'un char* passé en paramètres soit composé de nombres entre 0 et nb_etats-1
 * \author Ionas
 * \param s est le char* sur lequel on va tester s'il c'est un type correcte
 * \param nb_etats est le nombre d'états d'une règle
 * \return true si c'est un char* de type correcte, false sinon
 */

bool est_regle_correcte(char* s, unsigned int nb_etats){
    size_t taille = strlen(s);
    for(unsigned int i = 0; i < taille; i++){
        if(s[i] < 48 || s[i] > 48 + ((int)nb_etats) - 1){
            return false;
        }
    }
    return true;
}


/**
 * \fn void manuel()
 * \brief Cette fonction affiche le manuel
 * \author Samir
 */

void manuel(){
    printf("Bienvenue dans le manuel !\n\n");
    printf("Ce programme vous permet de générer un automate cellulaire en fonction de plusieurs paramètres.\n");
    printf("Afin de correctement générer un automate, plusieurs options sont disponibles : \n\n");
    printf("Il est tout d'abord possible de générer l'automate cellulaire en utilisant un fichier de configuration, cela peut se faire en utilisant l'argument '-f' ou '--file' suivi du nom du fichier à utiliser.\n");
    printf("Ce fichier doit être placer dans le dossier 'cfg' et doit absolument respecter les modèles déjà présent dans ce dossier.\n\n");
    printf("EXEMPLE : ./automate -f nom_du_fichier.config\n\n");
    printf("NOTE : Le nombre d'état ne doit être précisé dans le cas unique où vous créez votre propre règle. Il n'est donc pas nécessaire de préciser ce nombre lors de l'utilisation de la règle de Wolfram ou Somme\n\n");
    printf("Il est également possible de générer un automate  en passant des arguments directement au programme, cela peut se faire en utilisant l'argument '-a' ou '--args' suivi des paramètres dont voici l'ordre :\n\n");
    printf("NOMBRE_ITERATIONS  DIMENSION_MAX  CONFIGURATION_INITIALE  REGLE  TYPE_REGLE  TYPE_AFFICHAGE  [NB_ETATS]\n\n");
    printf("EXEMPLE : ./automate -a 16 11 00000100000 30 0 1\n\n");
    printf("- Le nombre d'itération doit etre un entier positif\n");
    printf("- La dimension max doit être un entier positif\n");
    printf("- La taille de la configuration initiale doit être égale à la dimension max, et ne doit comporter que des chiffres compris entre 0 et le nombre d'états possibles\n");
    printf("- La règle somme est une succession de 10 entier compris entre 0 et 3\n");
    printf("- La règle de Wolfram est un entier compris entre 0 et 255\n\n");
    printf("NOTE : Dans le cas d'une règle personnalisée, vous devrez concevoir son implémentation ainsi que sa règle d'affichage dans le code\n\n");
    printf("- Type règle est 0 pour une règle de Wolfram, 1 pour une règle somme, 2 pour une règle personnalisée\n");
    printf("- Type affichage est 0 pour un affichage dans la console, 1 pour la génération d'une image de l'automate\n");
    printf("Nombre d'états corresponds aux états possibles pour une cellule, ce chiffre, positif, ne doit être précisé seulement dans le cas de l'utilisation d'une règle personnalisée\n\n");
    printf("Enfin, il est possible de générer un automate en utilisant la lecture runtime, c'est à dire pendant l'exécution du programme, cela se fait en ne passant aucun arguments au programme.\n");
    printf("Les règles à respecter sont identiques à celles cîtées plus haut.\n\n");
    printf("NOTE : Tant que vous ne rentrerez pas une valeur correcte vérifiant chacunes de ces règles, le programme vous redemandera la valeur.\n\n");
    printf("Merci d'avoir lu ce manuel, bon courage !\n");
}