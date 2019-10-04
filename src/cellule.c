/**
 * \file cellule.c
 * \brief Ce fichier s'occupe des cellules.
 * \author Ionas Samir
 *
 */

#include "../include/cellule.h"


/**
 * \struct cellule
 * \brief Cette structure nous permet de savoir l'état d'une cellule ainsi que ses voisins
 * \author Ionas
 * 
 * Cette structure possede 3 valeurs :
 * -etat : int, qui represente l'état de la cellule
 * -voising_g : cellule* est le voisin gauche de la cellule actuelle
 * -voising_d : cellule* est le voisin droite de la cellule actuelle
 */

struct cellule {
    int etat;
    struct cellule* voisin_g;
    struct cellule* voisin_d;
};


/**
 * \fn cel creer_cellule()
 * \brief fonction qui crée une cellule et qui affecte ses voisins à null et son etat à 0.
 * \author Ionas
 * \return la nouvelle cellule créée.
 */

cel creer_cellule(){
    cel nouvelle_cel =  (cel) malloc (sizeof(struct cellule));
    nouvelle_cel->etat = 0;
    nouvelle_cel->voisin_d = NULL;
    nouvelle_cel->voisin_g = NULL;
    return nouvelle_cel ;
}


/**
 * \fn void supprimer_cellule(cel* cellule)
 * \brief fonction qui supprime la cellue en faisant le free de cette cellule et en metant le pointeur vers NULL.
 * \author Ionas
 * \param cellule est la cellule à supprimer
 */

void supprimer_cellule(cel* cellule){
    free(*cellule);
    *cellule=NULL;
}

/**
 * \fn void set_voisin_droite(cel actuelle,cel droite)
 * \brief fonction qui associe deux cellules entre-elles.
 * \author Ionas
 * \param actuelle est la cellule actuelle à laquelle on va ajouter une cellule à droite
 * \param droite est la cellue de droite à laquelle on va ajouter une cellule à gauche
 */

void set_voisin_droite(cel actuelle,cel droite){
    actuelle->voisin_d = droite;
    droite->voisin_g = actuelle;
}

/**
 * \fn void set_voisin_gauche(cel actuelle,cel gauche)
 * \brief fonction qui associe deux cellules entre-elles.
 * \author Ionas
 * \param actuelle est la cellule actuelle à laquelle on va ajouter une cellule à gauche
 * \param gauche est la cellue de gauche à laquelle on va ajouter une cellule à droite
 */

void set_voisin_gauche(cel actuelle,cel gauche){
    actuelle->voisin_g = gauche;
    gauche->voisin_d = actuelle;
}

void set_etat(cel cellule,int etat){
    cellule->etat = etat;
}

cel get_voisin_droite(cel c){
    return c->voisin_d;
}

cel get_voisin_gauche(cel c){
    return c->voisin_g;
}

/**
 * \fn int get_etat(cel c)
 * \brief Fonction qui retourne l'état de la cellule c, si cette cellule est NULL alors elle retourne 0
 * \author Ionas
 * \param c est la cellule
 * \return l'état de la cellule c
 */

int get_etat(cel c){
    if (c == NULL)
        return 0;
    return c->etat;
}

/**
 * \fn int etat_suivant(cel cellule,char * regle, int (*type_regle) (char*, int* etats))
 * \brief Cette fonction retourne l'état suivant d'une cellule en fonction de la regle, du type de regle et de ses voisins
 * \author Ionas
 * \param cellule est la cellule sur laquelle on va generer l'état suivant
 * \param regle est la regle sur laquelle on se base pour generer l'état suivant
 * \param type_regle est la fonction de la type de regle, soit Wolfram soit Somme soit une autre défini par l'utilisateur
 * \return l'état de la cellule c au temps t+1
 */

int etat_suivant(cel cellule,char * regle, int (*type_regle) (char*, int* etats)){
    int etat_gauche, etat_droite, etat_milieu;
    etat_gauche=cellule->voisin_g->etat;
    etat_droite=cellule->voisin_d->etat;
    etat_milieu=cellule->etat;
    size_t taille_tab = 3; 
    int* tab_etats = (int*) malloc (sizeof(int) * taille_tab);
    tab_etats[0] = etat_gauche;
    tab_etats[1] = etat_milieu;
    tab_etats[2] = etat_droite;
    int x = type_regle(regle, tab_etats); 
    return x;
}

/**
 * \fn void afficher_cellule(cel cellule, void (*affichage_cellule) (int) )
 * \brief cette fonction affiche une cellule en fonction de la fonction D'affichage de la cellule
 * \author Samir
 * \param cellule est la cellule a afficher
 * \affichage_cellule est la fonction d'affichage de la cellule
 * 
 */
void afficher_cellule(cel cellule, void (*affichage_cellule) (int) ){
    affichage_cellule(cellule->etat);
}


