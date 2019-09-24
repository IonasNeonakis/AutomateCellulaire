#include "../include/automate.h"
#include "../include/affichage.h"

struct automate {
    unsigned int temps ; // le temps t actuelle, commence à 0
    cel** configuration_actuelle ; //chauqe char est un etat
    unsigned int dimension_max; // en gros la taille du tableau
    unsigned int nb_iterations_max; //
    char* regle; // la regle a appliquer  (00011110) 2 = 30 || 0013100132 pour la somme
    int (*type_regle) (char*, unsigned int, unsigned int, unsigned int);
    void (*affichage_regle) (int);
    unsigned int nb_etats; //pas sûr wolfran =2(0,1) ; somme = 4(0,1,2,3)
    void (*affichage) (automate);
    char *configuration_initiale ; 
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
void afficher_automate(automate automate_cellulaire){
    automate_cellulaire->affichage(automate_cellulaire);
}

void set_affichage_regle(automate a,void (*afficher_cellule)(int)){
    a->affichage_regle = afficher_cellule;
}

void set_affichage(automate a ,void (*afficher_automate)(automate)){
    a->affichage = afficher_automate;
}

void set_type_regle(automate a ,int (*regle)(char*, unsigned int, unsigned int, unsigned int)){
    a->type_regle = regle;
}

void set_regle(automate a, char* regle_binaire){
    a->regle = regle_binaire;
}

void set_configuration_initiale(automate automate_cellulaire, char* configuration_initiale){
    for(unsigned int i = 0; i < automate_cellulaire->dimension_max; i++){
        automate_cellulaire->configuration_actuelle[0][i] = creer_cellule();
        //printf("%d ", configuration_initiale[i] == '0');
        set_etat(automate_cellulaire->configuration_actuelle[0][i], configuration_initiale[i] == '0' ? 0 : 1);
    }
    automate_cellulaire->configuration_initiale = configuration_initiale;
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

cel** generer_automate(automate automate_cellulaire){
    //set_configuration_initiale(automate_cellulaire, automate_cellulaire->configuration_initiale);
    //automate_cellulaire->regle = regle;
    //automate_cellulaire->type_regle = type_regle;
    //automate_cellulaire->affichage_regle = affichage_regle;
    for(int i = 0; i <(int) automate_cellulaire->dimension_max; i++){
        printf("%d", get_etat(automate_cellulaire->configuration_actuelle[0][i]));
    }
    set_voisins(automate_cellulaire, 0);
    //char* regle_binaire = conversion_decimal_binaire(regle);
    for(unsigned int i = 1; i < automate_cellulaire->nb_iterations_max; i++){
        for(unsigned int j = 0; j < automate_cellulaire->dimension_max; j++){
            cel cellule = creer_cellule();
            set_etat(cellule, etat_suivant(automate_cellulaire->configuration_actuelle[i-1][j], automate_cellulaire->regle, automate_cellulaire->type_regle));
            automate_cellulaire->configuration_actuelle[i][j] = cellule;
        }
        set_voisins(automate_cellulaire, i);
    }
    //free(regle_binaire);
    return automate_cellulaire->configuration_actuelle;
}

automate lire_fichier_automate(){
    unsigned int nb_iterations =0 ;
    unsigned int dimension =0;
    unsigned int nb_etats =0;
    char* regle =NULL;
    
    char* config_init=NULL;
    int (*type_regle)(char*, unsigned int, unsigned int, unsigned int) = NULL;
    void (*type_affichage)(automate) =NULL;
    void (*affichage_cellule)(int)=NULL;

    
    //mettre des sets dans le main
    FILE* fp;
    char chaine[200];

    regex_t preg;
    int err ; 
    const char *str_regex = "\"(type_affichage|type_regle|nb_iteration|dimension|config_init|nb_etats|regle)\"=([0123456789]*);$" ;

    err = regcomp(&preg ,str_regex, REG_EXTENDED | REG_NEWLINE); 

    if (err==1){
        printf("erreur compliation regex");
        exit(1);
    }

    fp=fopen("cfg/test1.config","r");
    if (fp==NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier en lecture");
    }

    int match;
    size_t nmatch=0;
    regmatch_t *pmatch = NULL;

    nmatch=preg.re_nsub;



    char *type ;
    int start_type ;
    int end_type ;
    size_t size_type ;

    char *valeur;
    int start_valeur;
    int end_valeur;
    size_t size_valeur;


    while(fgets(chaine,200,fp)!=NULL){
        printf("%s",chaine);

        pmatch = realloc (pmatch,sizeof (*pmatch)*nmatch);

        if (pmatch){
            match= regexec(&preg,chaine,nmatch,pmatch,0);
            //regfree (&preg);
        }            

        if (match==0){
            printf("motif correct\n");

            type = NULL;
            valeur = NULL;
            start_type = pmatch[1].rm_so;
            end_type = pmatch[1].rm_eo;
            size_type = end_type - start_type;



            start_valeur = pmatch[1].rm_eo+2;
            end_valeur = pmatch[0].rm_eo-1;
            size_valeur = end_valeur - start_valeur;


               
            type = realloc (type,sizeof (*type) * (size_type + 1));
            valeur=realloc(valeur,sizeof(*valeur)*(size_valeur+1));
            if (type)
            {
               strncpy (type, &chaine[start_type], size_type);
               type[size_type] = '\0';
               printf ("type ici : %s\n", type);
            }
            if(valeur){
                strncpy (valeur, &chaine[start_valeur], size_valeur);
                valeur[size_valeur] = '\0';
                printf ("val ici : %s\n", valeur);
            }

            if(!strcmp(type,"nb_iteration")){
                printf("je suis là %s \n\n",type);
                if(nb_iterations!=0){
                    printf("duplication du type \"nb_iteration\". Arrêt du programme\n");
                    exit(1);
                }else
                    nb_iterations=(unsigned int)conversion_char_int(valeur);

            }else if(!strcmp(type,"dimension")){
                if(dimension!=0){
                    printf("duplication du type \"dimension\". Arrêt du programme\n");
                    exit(1);
                }else
                    dimension=(unsigned int) conversion_char_int(valeur);

            }else if(!strcmp(type,"regle")){
                if (regle!=NULL){
                    printf("duplication du type \"regle\". Arrêt du programme\n");
                    exit(1);
                }else{
                    regle = (char*) malloc (sizeof(char) * strlen(valeur) + 1);
                    regle = strcpy(regle, valeur);
                    printf("\n\n\nicicicicicici ::::: %s \n",regle);
                    //regle[strlen(regle)-1]="\0";
                }
                
            }else if(!strcmp(type,"config_init")){
               if (config_init!=NULL){
                    printf("duplication du type \"config_init\". Arrêt du programme\n");
                    exit(1);
                }else
                config_init=valeur;
                
            }else if(!strcmp(type,"nb_etats")){
                if(nb_etats!=0){
                    printf("duplication du type \"nb_etats\". Arrêt du programme\n");
                    exit(1);
                }else
                nb_etats=(unsigned int) conversion_char_int(valeur);
            }else if(!strcmp(type,"type_regle")){
                if(type_regle!=NULL){
                    printf("duplication du type \"type_regle\". Arrêt du programme\n");
                    exit(1);
                }else{
                    switch (conversion_char_int(valeur)){
                    case 0:
                        type_regle = &regle_binaire;
                        affichage_cellule = &afficher_cellule_binaire;
                        break;
                    case 1:
                        type_regle = &regle_somme;
                        affichage_cellule = &afficher_cellule_somme;
                        break;
                    default:
                        printf("Erreur de la regle, arrêt du programme.");
                        exit(1);
                        break;
                    }
                }
            }else if(!strcmp(type,"type_affichage")){
                if(type_affichage != NULL){
                    printf("duplication du type \"type_affichage\". Arrêt du programme\n");
                    exit(1);
                }else{
                    switch (conversion_char_int(valeur)){
                    case 0:
                        type_affichage=&afficher_automate_console;
                        break;
                    case 1:
                        type_affichage=&afficher_automate_pgm;
                        break;
                    default:
                        printf("Erreur de l'affichage, arrêt du programme.");
                        exit(1);
                        break;
                    }
                }

            }else{
                printf("\n\nerreur type inconnu\n\n");
                exit(1);
            }
            
            free (type);
            free (valeur);

        }else{
            printf("Fichier corrompu\n");
            exit(1);
        }

    }
    if(dimension == 0 || regle == NULL || nb_etats == 0 || config_init == NULL || nb_iterations == 0 ||type_affichage==NULL ||type_regle==NULL){
        printf("Fichier incomplet pour l'éxecution du programme. Arrêt du programme\n");
        exit(1);
    }
    printf("\n\n\nicicicicicici ::::: %s \n", regle);

    //regle[8]="\0";
    // automate a= creer_automate(dimension,nb_iterations,nb_etats);
    // a->regle =regle;
    // a->configuration_initiale=config_init;
    // a->type_regle=type_regle;
    // a->affichage_regle=affichage_cellule;
    // a->affichage=type_affichage;
    // generer_automate(a);
    automate a= creer_automate(dimension,nb_iterations,nb_etats);
    //a->regle =regle;

    set_regle(a,regle);
    //a->configuration_initiale=config_init;
    set_configuration_initiale(a,config_init);
    set_type_regle(a,type_regle);
    //a->type_regle=type_regle;
    set_affichage_regle(a,affichage_cellule);
    //a->affichage_regle=affichage_cellule;
    set_affichage(a,type_affichage);;
    //a->affichage=type_affichage;
    generer_automate(a);

    free(pmatch);
    free(regle);
    regfree(&preg);

    fclose(fp);
    return a;
}
