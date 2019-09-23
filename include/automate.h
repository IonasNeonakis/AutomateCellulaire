#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <regex.h>
#include <stdlib.h>


#include "../include/cellule.h"
#include "../include/utils.h"
#include "../include/regles.h"
#include "../include/affichage.h"

struct automate;

typedef struct automate* automate;

automate creer_automate(unsigned int, unsigned int, unsigned int);

void supprimer_automate(automate*);

void afficher_automate(automate);

void set_configuration_initiale(automate, char*);

void set_voisins(automate, unsigned int);

cel** get_configuration_actuelle(automate);

unsigned int get_nb_iterations_max();

unsigned int get_dimension_max(automate);

char* get_regle(automate);

void (*get_affichage_regle(automate))(int);

cel** generer_automate(automate, char*, int (*) (char*, unsigned int, unsigned int, unsigned int), char*, void (*) (int));

automate lire_fichier_automate();

#endif