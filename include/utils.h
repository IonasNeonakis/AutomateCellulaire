#ifndef UTILS_H
#define UTILS_h

#include <stdbool.h>

int conversion_binaire_decimal(int, int, int);

char* conversion_decimal_binaire(int);

int conversion_char_int(char*);

bool est_un_int(char *s);

bool est_regle_binaire(char *);

bool est_regle_somme(char * );

bool est_de_longueur(char *,int);

bool est_regle_correcte(char*, unsigned int);

#endif