#include "../include/automate.h"

struct automate {
    unsigned int temps ; // le temps t actuelle, commence à 0
    cel** configuration_actuelle ; //chauqe char est un etat
    unsigned int dimension_max; // en gros la taille du tableau
    unsigned int nb_iterations_max; //
    char* regle; // la regle a appliquer  (00011110) 2 = 30 || 0013100132 pour la somme
    int (*type_regle) (char*, unsigned int, unsigned int, unsigned int);
    void (*affichage_regle) (int);
    unsigned int nb_etats; //pas sûr wolfran =2(0,1) ; somme = 4(0,1,2,3)
    //comment définir le types de transition a effectuer ? somme || configuration des voisins ?
};

automate creer_automate(unsigned int dimension_max, unsigned int nb_iterations_max, unsigned int nb_etats){
    automate automate_cellulaire = (automate) malloc (sizeof(struct automate));
    automate_cellulaire->temps = 0;
    automate_cellulaire->configuration_actuelle = (cel**) malloc (sizeof(cel*) * nb_iterations_max);
    for(unsigned int i = 0; i < nb_iterations_max; i++){
        automate_cellulaire->configuration_actuelle[i] = (cel*) malloc (sizeof(cel) * dimension_max);
    }
    automate_cellulaire->regle = NULL;
    automate_cellulaire->type_regle = NULL;
    automate_cellulaire->nb_iterations_max = nb_iterations_max;
    automate_cellulaire->dimension_max = dimension_max;
    automate_cellulaire->nb_etats = nb_etats;
    automate_cellulaire->affichage_regle = NULL;

    return automate_cellulaire;
}

void supprimer_automate(automate* automate_cellulaire_ptr){
    automate automate_cellulaire = *automate_cellulaire_ptr;
    for(unsigned int i = 0; i < automate_cellulaire->nb_iterations_max; i++){
        for(unsigned int j = 0; j < automate_cellulaire->dimension_max; j++){
            supprimer_cellule(&automate_cellulaire->configuration_actuelle[i][j]);
        }
        free(automate_cellulaire->configuration_actuelle[i]);
        automate_cellulaire->configuration_actuelle[i] = NULL;
    }
    free(automate_cellulaire->configuration_actuelle);
    automate_cellulaire->configuration_actuelle = NULL;
    free(automate_cellulaire);
    automate_cellulaire = NULL;
}
void afficher_automate(automate automate_cellulaire, void (*affichage) (automate)){
    affichage(automate_cellulaire);
}

void set_configuration_initiale(automate automate_cellulaire, char* configuration_initiale){
    for(unsigned int i = 0; i < automate_cellulaire->dimension_max; i++){
        automate_cellulaire->configuration_actuelle[0][i] = creer_cellule();
        set_etat(automate_cellulaire->configuration_actuelle[0][i], configuration_initiale[i] == '0' ? 0 : 1);
    }
}

void set_voisins(automate automate_cellulaire, unsigned int k){
    for(unsigned int i = 1; i < automate_cellulaire->dimension_max; i++){
        set_voisin_gauche(automate_cellulaire->configuration_actuelle[k][i], automate_cellulaire->configuration_actuelle[k][i - 1]);
    }
    set_voisin_gauche(automate_cellulaire->configuration_actuelle[k][0], automate_cellulaire->configuration_actuelle[k][automate_cellulaire->dimension_max - 1]);
}

cel** get_configuration_actuelle(automate automate_cellulaire){
    return automate_cellulaire->configuration_actuelle;
}

unsigned int get_nb_iterations_max(automate automate_cellulaire){
    return automate_cellulaire->nb_iterations_max;
}

unsigned int get_dimension_max(automate automate_cellulaire){
    return automate_cellulaire->dimension_max;
}

char* get_regle(automate automate_cellulaire){
    return automate_cellulaire->regle;
}

void (*get_affichage_regle(automate automate_cellulaire))(int){
    return automate_cellulaire->affichage_regle;
}

cel** generer_automate(automate automate_cellulaire, char* regle, int (*type_regle) (char*, unsigned int, unsigned int, unsigned int), char* configuration_initiale, void (*affichage_regle) (int)){
    set_configuration_initiale(automate_cellulaire, configuration_initiale);
    automate_cellulaire->regle = regle;
    automate_cellulaire->type_regle = type_regle;
    automate_cellulaire->affichage_regle = affichage_regle;
    set_voisins(automate_cellulaire, 0);
    //char* regle_binaire = conversion_decimal_binaire(regle);
    for(unsigned int i = 1; i < automate_cellulaire->nb_iterations_max; i++){
        for(unsigned int j = 0; j < automate_cellulaire->dimension_max; j++){
            cel cellule = creer_cellule();
            set_etat(cellule, etat_suivant(automate_cellulaire->configuration_actuelle[i-1][j], regle, type_regle));
            automate_cellulaire->configuration_actuelle[i][j] = cellule;
        }
        set_voisins(automate_cellulaire, i);
    }
    //free(regle_binaire);
    return automate_cellulaire->configuration_actuelle;
}

automate lire_fichier_automate(){
    unsigned int nb_iterations ;
    unsigned int dimension ;
    unsigned int nb_etats ;
    char* regle ;
    
    //mettre des sets dans le main
    FILE* fp;
    char chaine[200];

    regex_t regex;
    int result ; 
    result = regcomp(&regex ,"\"(nb_iteration|dimension|config_init|nb_etats|regle)\"=[0123456789]*;$", REG_EXTENDED | REG_NEWLINE); 

    if (result){
        printf("erreur compliation regex");
        exit(1);
    }

    fp=fopen("cfg/test1.config","r");
    if (fp==NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier en lecture");
    }
    while(fgets(chaine,200,fp)!=NULL){
        printf("%s",chaine);
        result=regexec(&regex,chaine,0,NULL,0);
        if (!result){
            printf("motif correct\n");
        }else{
            printf("motif incorrect\n");
        }

    }
    regfree(&regex);

    fclose(fp);
    return NULL;
}
