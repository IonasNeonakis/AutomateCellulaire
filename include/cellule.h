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

void set_voisin_droite(cel,cel);

void set_voisin_gauche(cel, cel);

void set_etat(cel, int );

int etat_suivant(cel, char*);


#endif