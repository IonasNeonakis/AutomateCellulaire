#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "../include/automate.h"
#include "../include/regle.h"

void afficher_cellule_binaire(int);

void afficher_cellule_somme(int);

void afficher_ligne(cel*, unsigned int, void (*) (int));

void afficher_automate_console(automate);

void afficher_automate_pgm(automate);

#endif