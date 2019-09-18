#include "../include/cellule.h"

struct cellule {
    int etat;
    struct cellule* voisin_g;
    struct cellule* voisin_d;
};

cel creer_cellule(){
    cel nouvelle_cel =  (cel) malloc (sizeof(struct cellule));
    nouvelle_cel->etat = 0;
    nouvelle_cel->voisin_d = NULL;
    nouvelle_cel->voisin_g = NULL;
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




int etat_suivant(cel cellule,char * regle, int (*type_regle) (char*, unsigned int, unsigned int, unsigned int)){
    int etat_gauche, etat_droite, etat_milieu;
    etat_gauche=cellule->voisin_g->etat;
    etat_droite=cellule->voisin_d->etat;
    etat_milieu=cellule->etat;
    int x = type_regle(regle,etat_gauche,etat_milieu,etat_droite); 
    return x;
}

void afficher_cellule(cel cellule){
    char car ;
    if (cellule->etat==0)
        car=' ';
    else
        car='X';
    
    printf("%c",car);
}


