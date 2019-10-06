#ifndef IO_H
#define IO_H

#include "./automate.h"
#include "./regle.h"

automate lire_fichier_automate(automate, char*);

void process_args(automate, int, char*[]);

void lecture_runtime_automate(automate);

void manuel();

#endif