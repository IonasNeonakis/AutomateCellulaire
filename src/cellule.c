#include "../include/cellule.h"

struct cellule {
    int etat;
    struct cellule* voisin_g;
    struct cellule* voisin_d;
};

cel creer_celule(int etat){

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

