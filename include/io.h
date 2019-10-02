#ifndef IO_H
#define IO_H

#include "./automate.h"
#include "./regle.h"

automate lire_fichier_automate(automate, regle, char*);

void process_args(automate, regle, int, char*[]);

void lecture_runtime_automate(automate a, regle);

void manuel();

#endif