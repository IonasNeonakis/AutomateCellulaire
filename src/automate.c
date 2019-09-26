#include "../include/automate.h"
#include "../include/affichage.h"

/**
 * \file automate.c
 * \brief Fichier se rapportant à la création d'un automate, sa gestion ainsi que son affichage
 * \author Ionas Samir
 *
 * Ce fichier permet de créer un automate à partir des paramètres donnés soit par arguments, soit par fichier, ou soit par lecture runtime. L'automate ainsi créé pourra s'afficher
 * selon une fonction d'affichage définie par l'utilisateur
 *
 */


/**
 * \struct automate automate.h
 * \brief Cette structure permet de représenter un automate
 * \author Ionas Samir
 * 
 * configuration_actuelle représente un tableau à deux dimension où chaque ligne représente une génération de cellule.
 * dimension_max représente le nombre de cellules maximum sur une ligne
 * nb_iterations_max représente le nombre de générations qui seront générées
 * _regle représente la règle de transition à suivre pour passer à la génération suivante
 * affichage est une fonction d'affichage de l'automate
 * configuration_initiale représente la configuration initiale de l'automate c'est à dire la configuration de cellule au temps t = 0
 */

struct automate {
    unsigned int temps ; // le temps t actuelle, commence à 0
    cel** configuration_actuelle ; //chauqe char est un etat
    unsigned int dimension_max; // en gros la taille du tableau
    unsigned int nb_iterations_max; //
    regle _regle;
    void (*affichage) (automate);
    char *configuration_initiale;
};

/**
 * \fn automate creer_automate (unsigned int dimension_max, unsigned int nb_iterations_max)
 * \brief Fonction de création de l'automate, allocation de la mémoire pour le tableau à deux dimensions, et passage des valeurs de dimension_max et nb_iterations_max dans la structure.
 * \author Samir
 *
 * \param unsigned int dimension_max représente le nombre de cellules maximum sur une ligne
 * \param unsigned int nb_iterations_max représente le nombre de générations qui seront générées
 * \return automate ainsi créé
 */

automate creer_automate(unsigned int dimension_max, unsigned int nb_iterations_max){
    automate automate_cellulaire = (automate) malloc (sizeof(struct automate));
    automate_cellulaire->temps = 0;
    automate_cellulaire->configuration_actuelle = (cel**) malloc (sizeof(cel*) * nb_iterations_max);
    for(unsigned int i = 0; i < nb_iterations_max; i++){
        automate_cellulaire->configuration_actuelle[i] = (cel*) malloc (sizeof(cel) * dimension_max);
    }
    automate_cellulaire->_regle = NULL;
    automate_cellulaire->nb_iterations_max = nb_iterations_max;
    automate_cellulaire->dimension_max = dimension_max;

    return automate_cellulaire;
}

/**
 * \fn automate supprimer_automate (automate* automate_cellulaire_ptr)
 * \brief Fonction de suppression de l'automate, désallocation de la mémoire.
 * \author Samir
 *
 * \param automate* automate_cellulaire représente l'automate à supprimer
 */

void supprimer_automate(automate* automate_cellulaire_ptr){
    automate automate_cellulaire = *automate_cellulaire_ptr;
    for(unsigned int i = 0; i < automate_cellulaire->nb_iterations_max; i++){
        for(unsigned int j = 0; j < automate_cellulaire->dimension_max; j++){
            supprimer_cellule(&automate_cellulaire->configuration_actuelle[i][j]);
        }
        free(automate_cellulaire->configuration_actuelle[i]);
        automate_cellulaire->configuration_actuelle[i] = NULL;
    }
    free(automate_cellulaire->configuration_actuelle);
    automate_cellulaire->configuration_actuelle = NULL;
    free(automate_cellulaire->configuration_initiale);
    automate_cellulaire->configuration_initiale=NULL;
    supprimer_regle(&automate_cellulaire->_regle);
    automate_cellulaire->_regle=NULL;
    free(automate_cellulaire);
    automate_cellulaire = NULL;
}

/**
 * \fn automate afficher_automate (automate automate_cellulaire)
 * \brief Fonction d'affichage de l'automate.
 * \author Samir
 *
 * \param automate* automate_cellulaire représente l'automate à afficher
 */

void afficher_automate(automate automate_cellulaire){
    automate_cellulaire->affichage(automate_cellulaire);
}

void set_affichage(automate a ,void (*afficher_automate)(automate)){
    a->affichage = afficher_automate;
}

/**
 * \fn void set_configuration_initiale (automate automate_cellulaire, char* configuration_initiale)
 * \brief Fonction permettant de définir correctement l'état initial de l'automate.
 * \author Samir
 *
 * La configuration initiale sera mise en place avec les états de cellules correspondants
 * 
 * \param automate automate_cellulaire représente l'automate sur lequel la fonction va opérer
 * \param char* configuration_initiale représente la configuration initiale à passer
 */

void set_configuration_initiale(automate automate_cellulaire, char* configuration_initiale){
    for(unsigned int i = 0; i < automate_cellulaire->dimension_max; i++){
        automate_cellulaire->configuration_actuelle[0][i] = creer_cellule();
        set_etat(automate_cellulaire->configuration_actuelle[0][i], configuration_initiale[i] == '0' ? 0 : 1);
    }
    automate_cellulaire->configuration_initiale = (char*) malloc (sizeof(char) * strlen(configuration_initiale) + 1);
    strcpy(automate_cellulaire->configuration_initiale, configuration_initiale);
}

/**
 * \fn void set_voisins(automate automate_cellulaire, unsigned int k)
 * \brief Fonction permettant de définir correctement les voisins de chaque cellule
 * \author Samir
 * 
 * On réalise cette opération en partant de la seconde cellule et en mettant la cellule à la position j - 1 comme son voisin de gauche 
 * 
 * \param automate automate_cellulaire représente l'automate sur lequel la fonction va opérer
 * \param unsigned int k représente la ligne, soit la génération de cellule concernée
 */

void set_voisins(automate automate_cellulaire, unsigned int k){
    for(unsigned int i = 1; i < automate_cellulaire->dimension_max; i++){
        set_voisin_gauche(automate_cellulaire->configuration_actuelle[k][i], automate_cellulaire->configuration_actuelle[k][i - 1]);
    }
    set_voisin_gauche(automate_cellulaire->configuration_actuelle[k][0], automate_cellulaire->configuration_actuelle[k][automate_cellulaire->dimension_max - 1]);
}

cel** get_configuration_actuelle(automate automate_cellulaire){
    return automate_cellulaire->configuration_actuelle;
}

unsigned int get_nb_iterations_max(automate automate_cellulaire){
    return automate_cellulaire->nb_iterations_max;
}

unsigned int get_dimension_max(automate automate_cellulaire){
    return automate_cellulaire->dimension_max;
}

char* get_regle_automate(automate automate_cellulaire){
    return get_regle(automate_cellulaire->_regle);
}

void (*get_affichage_regle_automate(automate automate_cellulaire))(int){
    return get_affichage_regle(automate_cellulaire->_regle);
}

void set_regle_automate(automate automate_cellulaire, regle r){
    automate_cellulaire->_regle = r;
}


/**
 * \fn cel** generer_automate(automate automate_cellulaire)
 * \brief Fonction permettant de générer l'automate
 * \author Samir
 * 
 * On génère l'automate en utilisant sa règle de transition jusqu'au nombre d'itérations maximum défini pour l'automate. Pour ce faire, on part de la première génération à réellement génerer,
 * et pour chaque cellule on va venir appliquer la règle, redéfinir l'état de la cellule et redéfinir les différents voisins.
 * 
 * \param automate automate_cellulaire représente l'automate sur lequel la fonction va opérer
 * \return cel** le tableau à deux dimensions de générations de cellules
 */

cel** generer_automate(automate automate_cellulaire){
    set_voisins(automate_cellulaire, 0);
    for(unsigned int i = 1; i < automate_cellulaire->nb_iterations_max; i++){
        for(unsigned int j = 0; j < automate_cellulaire->dimension_max; j++){
            cel cellule = creer_cellule();
            regle r = automate_cellulaire->_regle;
            set_etat(cellule, etat_suivant(automate_cellulaire->configuration_actuelle[i-1][j], get_regle(r), get_type_regle(r)));
            automate_cellulaire->configuration_actuelle[i][j] = cellule;
        }
        set_voisins(automate_cellulaire, i);
    }
    return automate_cellulaire->configuration_actuelle;
}