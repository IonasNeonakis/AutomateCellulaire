

struct cellule {
    int etat;
    struct cellule* voisin_g;
    struct cellule* voisin_d;
};

typedef struct cellule* cel;

struct automate {
    int temps ; // le temps t actuelle, commence à 0
    cel * configuration_actuelle ; //chauqe char est un etat
    int dimension_max; // en gros la taille du tableau
    int nb_iterations ; //
    int regle ; // la regle a appliquer  (00011110) 2 = 30 || 0013100132 pour la somme 
    int nombre_etats ; //pas sûr wolfran =2(0,1) ; somme = 4(0,1,2,3)
    //comment définir le types de transition a effectuer ? somme || configuration des voisins ?
};

//configuration_actuelle[15]
// for (int i=0;i<dimension_max;i++){
//     cel a = genererSuivant(configuration_actuelle[i])
//     cel * configuration_suivante[i]=a;
// }