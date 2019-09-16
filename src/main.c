#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"
#include "../include/cellule.h"


int main(int argc, char* argv[]){

    cel a = creer_cellule();

    supprimer_cellule(&a);
    
    return EXIT_SUCCESS;
}