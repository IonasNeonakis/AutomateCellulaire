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

cel get_voisin_droite(cel c){
    return c->voisin_d;
}

cel get_voisin_gauche(cel c){
    return c->voisin_g;
}

int get_etat(cel c){
    if (c==NULL)
        return 0;
    return c->etat;
}


int etat_suivant(cel cellule,char * regle_binaire){
    int etat_gauche, etat_droite, etat_milieu;
    if (cellule->voisin_g==NULL)
        etat_gauche=0;
    else
        etat_gauche=cellule->voisin_g->etat;
    

    if (cellule->voisin_d==NULL)
        etat_droite=0;
    else
        etat_droite=cellule->voisin_d->etat;

    etat_milieu=cellule->etat;
    int x = conversion_binaire_decimal(etat_gauche,etat_milieu,etat_droite);
    return regle_binaire[strlen(regle_binaire)-1-x]-48;
}

void afficher_cellule(cel cellule){
    printf("%d\n",cellule->etat);
}


