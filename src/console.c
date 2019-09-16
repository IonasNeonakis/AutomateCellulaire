#include "../include/console.h"


char* lire_arguments(int argc,char* argv []){
    char* tab = {argv[1],argv[2],argv[3]};
    return tab;
}


void afficher_tout(int regle,char * regle_binaire,int iterations, int dimensions)