#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <stdlib.h>
#include <regex.h>


#include "../include/cellule.h"
#include "../include/utils.h"
#include "../include/regle.h"

struct automate;

typedef struct automate* automate;

automate creer_automate(unsigned int, unsigned int);

void supprimer_automate(automate*);

void afficher_automate(automate);

void set_affichage(automate,void (*afficher_automate_console)(automate));

void set_regle_automate(automate, regle);

void set_configuration_initiale(automate, char*);

void set_voisins(automate, unsigned int);

cel** get_configuration_actuelle(automate);

unsigned int get_nb_iterations_max();

unsigned int get_dimension_max(automate);

char* get_regle_automate(automate);

void (*get_affichage_regle_automate(automate))(int);

cel** generer_automate(automate);

automate lire_fichier_automate();

automate lecture_runtime_automate();

#endif