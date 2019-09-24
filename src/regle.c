#include "../include/regle.h"
#include "../include/utils.h"

struct regle {
    char* _regle; // la regle a appliquer  (00011110) 2 = 30 || 0013100132 pour la somme par ex
    int (*_type_regle) (char*, unsigned int, unsigned int, unsigned int);
    void (*_affichage_regle) (int);
};

regle creer_regle(){
    regle r = (regle) malloc (sizeof(struct regle));
    r->_regle = NULL;
    r->_type_regle = NULL;
    r->_affichage_regle = NULL;

    return r;
}

void supprimer_regle(regle* r){
    regle regle_a_supprimer = *r;
    free(regle_a_supprimer);
    regle_a_supprimer->_regle = NULL;
    regle_a_supprimer->_type_regle = NULL;
    regle_a_supprimer->_affichage_regle = NULL;
    regle_a_supprimer = NULL;
}

void set_regle(regle r, char* s){
    r->_regle = s;
}

void set_type_regle(regle r, int (*type_regle) (char*, unsigned int, unsigned int, unsigned int)){
    r->_type_regle = type_regle;
}

void set_affichage_regle(regle r, void (*affichage_regle) (int)){
    r->_affichage_regle = affichage_regle;
} 

char* get_regle(regle r){
    return r->_regle;
}

int (*get_type_regle(regle r))(char*, unsigned int, unsigned int, unsigned int){
    return r->_type_regle;
}

void (*get_affichage_regle(regle r))(int){
    return r->_affichage_regle;
}

int regle_binaire(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = conversion_binaire_decimal(e_cg, e_cm, e_cd);
    return regle[x] - 48;
}

int regle_somme(char* regle, unsigned int e_cg, unsigned int e_cm, unsigned int e_cd){
    int x = e_cg + e_cm + e_cd;
    return regle[x] - 48;
}