#ifndef IO_H
#define IO_H

#include "./automate.h"
#include "./regle.h"

automate lire_fichier_automate(regle, char*);

automate process_args(regle r,int argc, char* argv[]);

void lecture_runtime_automate(automate a, regle);

void manuel();

#endif