#ifndef CELLULE_H
#define CELLULE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/utils.h"

struct cellule;

typedef struct cellule* cel;

cel creer_cellule();

void supprimer_cellule(cel* );

void set_voisin_droite(cel, cel);

void set_voisin_gauche(cel, cel);

void set_etat(cel, int);

cel get_voisin_droite(cel);

cel get_voisin_gauche(cel);

int get_etat(cel);

int etat_suivant(cel cellule,char * regle, int (*type_regle) (char*, unsigned int, unsigned int, unsigned int));

void afficher_cellule(cel, void (*affichage_cellule) (int));

#endif