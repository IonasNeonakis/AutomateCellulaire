#include "../include/regles.h"
#include "../include/utils.h"

int regle_binaire(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = conversion_binaire_decimal(e_cg, e_cm, e_cd);
    return regle[x] - 48;
}

int regle_somme(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = e_cg + e_cm + e_cd;
    return regle[x] - 48;
}