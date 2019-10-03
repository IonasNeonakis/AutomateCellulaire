#ifndef REGLES_H
#define REGLES_H

#include <stdlib.h>

struct regle;

typedef struct regle* regle;

regle creer_regle();

void supprimer_regle(regle*);

void set_regle(regle, char*);

void set_type_regle(regle, int (*) (char*, int*));

void set_nb_etats(regle, unsigned int);

void set_taille_regle(regle r, unsigned int );

char* get_regle(regle);

int (*get_type_regle(regle))(char*, int*);

int get_nb_etats(regle);

int get_taille_regle(regle);

int regle_binaire(char*, int*);

int regle_somme(char*, int*);

#endif