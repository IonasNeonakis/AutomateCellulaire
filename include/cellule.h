#ifndef CELLULE_H
#define CELLULE_H

#include <stdio.h>
#include <stdlib.h>
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

int etat_suivant(cel, char*, int (*type_regle) (char*, int*));

void afficher_cellule(cel, void (*affichage_cellule) (int));

#endif