#ifndef REGLES_H
#define REGLES_H

#include <stdlib.h>

struct regle;

typedef struct regle* regle;

regle creer_regle();

void supprimer_regle(regle*);

void set_regle(regle, char*);

void set_type_regle(regle, int (*) (char*, unsigned int, unsigned int, unsigned int));

void set_affichage_regle(regle, void (*) (int));

void set_nb_etats(regle, unsigned int);

char* get_regle(regle);

int (*get_type_regle(regle))(char*, unsigned int, unsigned int, unsigned int);

void (*get_affichage_regle(regle))(int);

int get_nb_etats(regle);

int regle_binaire(char*, unsigned int, unsigned int, unsigned int);

int regle_somme(char*, unsigned int, unsigned int, unsigned int);

#endif