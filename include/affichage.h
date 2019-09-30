#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "../include/automate.h"
#include "../include/regle.h"

void afficher_cellule_binaire(int);

void afficher_cellule_somme(int);

void afficher_ligne(cel*, unsigned int, void (*) (int));

void afficher_automate_console_binaire(automate);

void afficher_automate_console_somme(automate);

void afficher_automate_pgm_binaire(automate);

void afficher_automate_pgm_somme(automate);

#endif