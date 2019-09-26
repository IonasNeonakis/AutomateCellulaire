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
    int taille;
    if (n==0){
        taille =-1;
    }else{
    taille = (int)floor(log2(n));
    }
    char* nombre_binaire = (char*) calloc (8, sizeof(char) * 8);
    int i = 0; 
    while (n > 0) {
        nombre_binaire[taille - i] = n % 2 + '0'; 
        n = n / 2; 
        i++; 
    }
    char* remplir = (char*) calloc (8, sizeof(char) * 8 + 1);
    for(int i = 0; i < 8-taille-1; i++){
        remplir[i] = '0';
    }
    remplir[8] = '\0';
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


