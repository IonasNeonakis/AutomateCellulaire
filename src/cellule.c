#include "../include/cellule.h"

struct cellule {
    int etat;
    struct cellule* voisin_g;
    struct cellule* voisin_d;
};

cel creer_cellule(){
    cel nouvelle_cel =  (cel) malloc (sizeof(struct cellule));
    nouvelle_cel->etat =0;
    nouvelle_cel->voisin_d=NULL;
    nouvelle_cel->voisin_g= NULL;
    return nouvelle_cel ;
}

void supprimer_cellule(cel* cellule){
    free(*cellule);
    *cellule=NULL;
}

void set_voisin_droite(cel actuelle,cel droite){
    actuelle->voisin_d=droite;
    droite->voisin_g=actuelle;
}

void set_voisin_gauche(cel actuelle,cel gauche){
    actuelle->voisin_g=gauche;
    gauche->voisin_d=actuelle;
}

void set_etat(cel cellule,int etat){
    cellule->etat=etat;
}


int etat_suivant(cel cellule,char * regle_binaire){
    int gauche = cellule->voisin_g->etat;
    int etat = cellule->etat;
    int droit = cellule->voisin_d->etat;
    int x = conversion_binaire_decimal(gauche,etat,droit);
    return strlen(regle_binaire-1-x);
}


