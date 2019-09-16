#ifndef CELLULE_H
#define CELLULE_H


struct cellule;

typedef struct cellule* cel;

void set_voisin_droite(cel,cel);

void set_voisin_gauche(cel actuelle,cel gauche);

#endif CELLULE_H