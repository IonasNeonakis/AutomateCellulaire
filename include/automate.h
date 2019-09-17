#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "../include/cellule.h"
#include "../include/utils.h"

struct automate;

typedef struct automate* automate;

automate creer_automate(unsigned int, unsigned int, unsigned int);

cel** generer_automate(automate, unsigned int, unsigned int, char*);

void supprimer_automate(automate);

void set_regle(automate, int);

void set_nb_iterations_max(automate, int);

void set_dimension_max(automate, int);

void set_configuration_initiale(automate, char*);

void set_voisins(automate, unsigned int);

void afficher_automate(automate);

void afficher_ligne(cel*, unsigned int);

#endif