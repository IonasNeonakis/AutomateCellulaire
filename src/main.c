#include <stdio.h>
#include <stdlib.h>

#include "../include/automate.h"

int main(int argc, char* argv[]){

    automate a = creer_automate(32, 16, 2);
    
    supprimer_automate(a);
    
    return EXIT_SUCCESS;
}