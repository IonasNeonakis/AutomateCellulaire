#include <stdlib.h>

#include "../include/automate.h"

struct automate {
    unsigned int temps ; // le temps t actuelle, commence à 0
    cel** configuration_actuelle ; //chauqe char est un etat
    unsigned int dimension_max; // en gros la taille du tableau
    unsigned int nb_iterations_max; //
    unsigned int regle; // la regle a appliquer  (00011110) 2 = 30 || 0013100132 pour la somme 
    unsigned int nb_etats; //pas sûr wolfran =2(0,1) ; somme = 4(0,1,2,3)
    //comment définir le types de transition a effectuer ? somme || configuration des voisins ?
};

automate creer_automate(unsigned int dimension_max, unsigned int nb_iterations_max, unsigned int nb_etats){
    automate automate_cellulaire = (automate) malloc (sizeof(struct automate));
    automate_cellulaire->temps = 0;
    automate_cellulaire->configuration_actuelle = (cel**) malloc (sizeof(cel*) * dimension_max);
    for(unsigned int i = 0; i < nb_iterations_max; i++){
        automate_cellulaire->configuration_actuelle[i] = (cel*) malloc (sizeof(cel) * dimension_max);
    }
    automate_cellulaire->nb_iterations_max = nb_iterations_max;
    automate_cellulaire->dimension_max = dimension_max;
    automate_cellulaire->nb_etats = nb_etats;

    return automate_cellulaire;
}

void supprimer_automate(automate automate_cellulaire){
    for(unsigned int i = 0; i < automate_cellulaire->nb_iterations_max; i++){
        free(automate_cellulaire->configuration_actuelle[i]);
        automate_cellulaire->configuration_actuelle[i] = NULL;
    }
    free(automate_cellulaire->configuration_actuelle);
    automate_cellulaire->configuration_actuelle = NULL;
    free(automate_cellulaire);
    automate_cellulaire = NULL;
}

//configuration_actuelle[15]
// for (int i=0;i<dimension_max;i++){
//     cel a = genererSuivant(configuration_actuelle[i])
//     cel * configuration_suivante[i]=a;
// }