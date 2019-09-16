#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "../include/cellule.h"
#include "../include/utils.h"

struct automate;

typedef struct automate* automate;

automate creer_automate(unsigned int, unsigned int, unsigned int);

void supprimer_automate(automate);

void afficher_automate(automate);

void afficher_ligne(cel*,unsigned int);

#endif