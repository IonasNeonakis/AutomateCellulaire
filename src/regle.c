
/**
 * \file regle.c
 * \brief Fichier se rapportant à la gestion des différentes règles pour l'automate ainsi qu'a la gestion de celles-ci
 * \author Ionas Samir
 *
 */

#include <stdio.h>
#include <string.h>

#include "../include/regle.h"
#include "../include/utils.h"

/**
 * \struct regle regle.h
 * \brief Cette structure permet de représenter une règle de transition
 * \author Samir
 * 
 * _regle représente la règle à appliquer, sous forme d'une succesion d'entier compris entre 0 et le nombre d'états
 * type_regle représente la fonction permettant d'appliquer la transition à la génération suivante de cellule
 * _affichage_regle correspond à la fonction d'affichage de la cellule, elle dépend de la règle, voilà pourquoi elle se situe ici
 * nb_etats représente le nombre d'états que peut prendre une cellule en fonction de la règle
 * taille_regle correspond à la longueur de la règle en caractère
 */

struct regle {
    char* _regle; // la regle a appliquer  (00011110) 2 = 30 || 0013100132 pour la somme par ex
    int (*_type_regle) (char*, int*);
    //void (*_affichage_regle) (int);
    unsigned int nb_etats;
    unsigned int taille_regle;
};

/**
 * \fn regle creer_regle 
 * \brief Fonction de création de la règle, allocation de la mémoire
 * \author Samir
 *
 * \return regle ainsi créée
 */

regle creer_regle(){
    regle r = (regle) malloc (sizeof(struct regle));
    r->_regle = NULL;
    r->_type_regle = NULL;
    //r->_affichage_regle = NULL;
    r->nb_etats = 0;
    r->taille_regle = 0;

    return r;
}

/**
 * \fn regle creer_regle 
 * \brief Fonction de suppression de la règle, désallocation de la mémoire
 * \author Samir
 *
 */

void supprimer_regle(regle* r){
    regle regle_a_supprimer = *r;
    free(regle_a_supprimer->_regle);
    regle_a_supprimer->_regle = NULL;
    regle_a_supprimer->_type_regle = NULL;
    free(regle_a_supprimer);
    regle_a_supprimer = NULL;
}

/**
 * \fn void set_regle(regle r, char* s)
 * \brief Fonction qui définie la règle
 * \author Samir
 *
 * Cette fonction effectue une copie de la règle passée en paramètre et la passe à la structure
 */

void set_regle(regle r, char* s){
    size_t taille_s = strlen(s);
    r->_regle = (char*) malloc (sizeof(char) * taille_s + 1);
    strcpy(r->_regle, s);
}

void set_type_regle(regle r, int (*type_regle) (char*, int*)){
    r->_type_regle = type_regle;
}

void set_nb_etats(regle r, unsigned int nb_etats){
    r->nb_etats = nb_etats;
}

void set_taille_regle(regle r, unsigned int taille_regle){
    r->taille_regle = taille_regle;
}

char* get_regle(regle r){
    return r->_regle;
}

int (*get_type_regle(regle r))(char*, int*){
    return r->_type_regle;
}

int get_nb_etats(regle r){
    return r->nb_etats;
}

int get_taille_regle(regle r){
    return r->taille_regle;
}

/**
 * \fn int regle_binaire(char* regle, int* etats)
 * \brief Cette fonction permet d'obtenir l'état d'une cellule après application de la règle de transition
 * \author Ionas
 *
 * \return l'état de la cellule après application de la règle de transition
 */

int regle_binaire(char* regle, int* etats){
    int x = conversion_binaire_decimal(etats[0], etats[1], etats[2]);
    free(etats);
    return regle[strlen(regle) - 1 - x] - 48;
}

int regle_somme(char* regle, int* etats){
    int x = etats[0] + etats[1] + etats[2];
    free(etats);
    return regle[x] - 48;
}

int regle_ionas(char* regle, int* etats){
    int x = etats[0] + etats[1] - etats[2];
    free(etats);
    if (x<0)
        x = 0;
    return regle[x] - 48;
}