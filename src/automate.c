#include "../include/automate.h"
#include "../include/affichage.h"

struct automate {
    unsigned int temps ; // le temps t actuelle, commence à 0
    cel** configuration_actuelle ; //chauqe char est un etat
    unsigned int dimension_max; // en gros la taille du tableau
    unsigned int nb_iterations_max; //
    regle _regle;
    void (*affichage) (automate);
    char *configuration_initiale;
};

automate creer_automate(unsigned int dimension_max, unsigned int nb_iterations_max){
    automate automate_cellulaire = (automate) malloc (sizeof(struct automate));
    automate_cellulaire->temps = 0;
    automate_cellulaire->configuration_actuelle = (cel**) malloc (sizeof(cel*) * nb_iterations_max);
    for(unsigned int i = 0; i < nb_iterations_max; i++){
        automate_cellulaire->configuration_actuelle[i] = (cel*) malloc (sizeof(cel) * dimension_max);
    }
    automate_cellulaire->_regle = NULL;
    automate_cellulaire->nb_iterations_max = nb_iterations_max;
    automate_cellulaire->dimension_max = dimension_max;

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
    free(automate_cellulaire->configuration_initiale);
    automate_cellulaire->configuration_initiale=NULL;
    supprimer_regle(&automate_cellulaire->_regle);
    automate_cellulaire->_regle=NULL;
    free(automate_cellulaire);
    automate_cellulaire = NULL;
}
void afficher_automate(automate automate_cellulaire){
    automate_cellulaire->affichage(automate_cellulaire);
}

void set_affichage(automate a ,void (*afficher_automate)(automate)){
    a->affichage = afficher_automate;
}

void set_configuration_initiale(automate automate_cellulaire, char* configuration_initiale){
    for(unsigned int i = 0; i < automate_cellulaire->dimension_max; i++){
        automate_cellulaire->configuration_actuelle[0][i] = creer_cellule();
        set_etat(automate_cellulaire->configuration_actuelle[0][i], configuration_initiale[i] == '0' ? 0 : 1);
    }
    automate_cellulaire->configuration_initiale = (char*) malloc (sizeof(char) * strlen(configuration_initiale) + 1);
    strcpy(automate_cellulaire->configuration_initiale, configuration_initiale);
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

char* get_regle_automate(automate automate_cellulaire){
    return get_regle(automate_cellulaire->_regle);
}

void (*get_affichage_regle_automate(automate automate_cellulaire))(int){
    return get_affichage_regle(automate_cellulaire->_regle);
}

void set_regle_automate(automate automate_cellulaire, regle r){
    automate_cellulaire->_regle = r;
}

cel** generer_automate(automate automate_cellulaire){
    set_voisins(automate_cellulaire, 0);
    for(unsigned int i = 1; i < automate_cellulaire->nb_iterations_max; i++){
        for(unsigned int j = 0; j < automate_cellulaire->dimension_max; j++){
            cel cellule = creer_cellule();
            regle r = automate_cellulaire->_regle;
            set_etat(cellule, etat_suivant(automate_cellulaire->configuration_actuelle[i-1][j], get_regle(r), get_type_regle(r)));
            automate_cellulaire->configuration_actuelle[i][j] = cellule;
        }
        set_voisins(automate_cellulaire, i);
    }
    return automate_cellulaire->configuration_actuelle;
}

automate lire_fichier_automate(regle r,char* nom_fichier){
    unsigned int nb_iterations = 0;
    unsigned int dimension = 0;
    unsigned int nb_etats=0;
    int type_regle=-1;
    char* regle_string = NULL;
    
    char* config_init = NULL;
    void (*type_affichage)(automate) = NULL;


    FILE* fp;
    char chaine[20000];

    regex_t preg;
    int err; 
    const char *str_regex = "\"(type_affichage|nb_etats|type_regle|nb_iteration|dimension|config_init|regle)\"=([0123456789]*);$" ;

    err = regcomp(&preg, str_regex, REG_EXTENDED | REG_NEWLINE); 

    if (err == 1){
        printf("Erreur à la compilation du regex !");
        exit(1);
    }
    char cfg[5]="cfg/\0";
    char* fichier_a_ouvrir =(char*) malloc(sizeof(char)*strlen(nom_fichier)+1+strlen(cfg));
    strcpy(fichier_a_ouvrir,cfg);
    strcat(fichier_a_ouvrir,nom_fichier);

    fp = fopen(fichier_a_ouvrir,"r");
    
    if (fp == NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier en lecture !");
        exit(1);
    }

    int match;
    size_t nmatch = 0;
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

    while(fgets(chaine,20000,fp) != NULL){

        pmatch = realloc(pmatch, sizeof(*pmatch) * nmatch);

        if (pmatch){
            match = regexec(&preg,chaine,nmatch,pmatch,0);
        }            

        if (match == 0){
            type = NULL;
            valeur = NULL;
            start_type = pmatch[1].rm_so;
            end_type = pmatch[1].rm_eo;
            size_type = end_type - start_type;

            start_valeur = pmatch[1].rm_eo+2;
            end_valeur = pmatch[0].rm_eo-1;
            size_valeur = end_valeur - start_valeur;
               
            type = realloc (type, sizeof(*type) * (size_type + 1));
            valeur = realloc(valeur, sizeof(*valeur) * (size_valeur + 1));
            
            if(type){
               strncpy(type, &chaine[start_type], size_type);
               type[size_type] = '\0';
            }

            if(valeur){
                strncpy (valeur, &chaine[start_valeur], size_valeur);
                valeur[size_valeur] = '\0';
            }

            if(!strcmp(type, "nb_iteration")){
                if(nb_iterations!=0){
                    printf("Duplication du type : \"nb_iteration\". Arrêt du programme !\n");
                    exit(1);
                }else{
                    nb_iterations=(unsigned int)conversion_char_int(valeur);
                }
            }else if(!strcmp(type, "dimension")){
                if(dimension != 0){
                    printf("Duplication du type : \"dimension\". Arrêt du programme !\n");
                    exit(1);
                }else if(config_init!=NULL && !est_de_longueur(config_init,conversion_char_int(valeur))){
                    printf("La configuration initiale doit etre de la même longuer que la dimension. Arrêt du programme !\n");
                    exit(1);
                }else{
                    dimension=(unsigned int) conversion_char_int(valeur);
                }
            }else if(!strcmp(type, "regle")){
                if (regle_string != NULL){
                    printf("Duplication du type : \"regle\". Arrêt du programme !\n");
                    exit(1);
                }else if(type_regle!=0 && !est_de_longueur(valeur,get_taille_regle(r))){    
                    printf("La regle n'est pas de la bonne longueur. Arrêt du programme !\n");
                    exit(1);
                }else if(nb_etats==0){
                    printf("nb_etat doit etre défini avant regle. Arrêt du programme !\n");
                    exit(1);
                }else if(type_regle!=0 && !est_regle_correcte(valeur,nb_etats)){
                    printf("Erreur de la saisie de la regle comparé aux nombre d'états. Arrêt du programme ! \n");
                    exit(1);
                }else{
                    regle_string = (char*) malloc (sizeof(char) * strlen(valeur) + 1);
                    if(type_regle==0 && (conversion_char_int(valeur)>255 || conversion_char_int(valeur)<0)){
                        printf("la regle binaire doit être entre 0 et 255. Arrêt du programe ! \n");
                        exit(1);
                    }else{
                        regle_string = strcpy(regle_string, conversion_decimal_binaire(conversion_char_int(valeur)));
                    }
                }


            }else if(!strcmp(type, "config_init")){
               if (config_init != NULL){
                    printf("Duplication du type : \"config_init\". Arrêt du programme !\n");
                    exit(1);
                }else if(dimension!=0 && !est_de_longueur(valeur,dimension)){
                    printf("La dimension doit etre de la même longuer que la configuration initiale. Arrêt du programme !\n");
                    exit(1);
                }else if(nb_etats==0){
                    printf("nb_etats doit etre défini avant config_init. Arrêt du programme !\n");
                    exit(1);
                }else if(!est_regle_correcte(valeur,nb_etats)){
                    printf("Erreur de la saisie de la regle comparé aux nombre d'états. Arrêt du programme ! \n");
                    exit(1);
                }else{
                    config_init = (char*) malloc (sizeof(char) * strlen(valeur) + 1);
                    config_init = strcpy(config_init, valeur);
                }
            }else if(!strcmp(type, "nb_etats")){
                if(type_regle==0 || type_regle==1){
                    printf("nb_etats ne doit pas être défini si type_regle vaut 0 ou 1. Arrêt du programme ! \n");
                    exit(1);
                }else if(type_regle==-1){
                    printf("Le type de regle doit être défini avant nb_etats. Arrêt du programme ! \n");
                    exit(1);
                }else if(nb_etats!=0){
                    printf("Duplication du type : \"nb_iteration\". Arrêt du programme !\n");
                    exit(1);
                }else if(conversion_char_int(valeur)>9){
                    printf("le nombre d'états ne peut être supérieur à 9. Arrêt du programme ! \n");
                    exit(1);
                }else{
                    nb_etats=(unsigned int)conversion_char_int(valeur);
                }
            }else if(!strcmp(type, "type_affichage")){
                if(type_affichage != NULL){
                    printf("Duplication du type : \"type_affichage\". Arrêt du programme !\n");
                    exit(1);
                }else{
                    switch(conversion_char_int(valeur)){
                        case 0: {
                            type_affichage=&afficher_automate_console;
                            break;
                        }
                        case 1: {
                            type_affichage=&afficher_automate_pgm;
                            break;
                        }
                        default: {
                            printf("Erreur de l'affichage, arrêt du programme.");
                            exit(1);
                            break;
                        }
                    }
                }
            }else if(!strcmp(type,"type_regle")){
                if(type_regle!=-1){
                    printf("Duplication du type : \"type_regle\". Arrêt du programme !\n");
                    exit(1);
                }else{
                    switch (conversion_char_int(valeur)){
                        case 0: {
                            set_type_regle(r, &regle_binaire);
                            set_taille_regle(r, 8);
                            set_affichage_regle(r, &afficher_cellule_binaire);
                            nb_etats=2;
                            type_regle=0;
                            break;
                        }case 1 :{
                            set_type_regle(r, &regle_somme);
                            set_taille_regle(r, 10);
                            set_affichage_regle(r, &afficher_cellule_somme);
                            nb_etats=4;
                            type_regle=1;
                            break;
                        }case 2 : {
                            type_regle=2;
                            break;
                        }
                        default:{
                            printf("Erreur de type_regle. Arrêt du programme ! \n");
                            exit(1);
                            break;
                        }
                    }
                }


            }else{
                printf("\n\nErreur type inconnu !\n\n");
                exit(1);
            }

            free (type);
            free (valeur);

        }else{
            printf("Fichier corrompu !\n");
            exit(1);
        }
    }
    if(dimension == 0 || regle_string == NULL || config_init == NULL || nb_iterations == 0 ||type_affichage== NULL || type_regle==-1 || (nb_etats == 0 && type_regle==2)){
        printf("Fichier incomplet pour l'éxecution du programme. Arrêt du programme !\n");
        exit(1);
    }

    automate a = creer_automate(dimension,nb_iterations);
    
    set_regle(r, regle_string);
    set_nb_etats(r, nb_etats);
    set_regle_automate(a, r);

    set_configuration_initiale(a, config_init);
    set_affichage(a,type_affichage);

    generer_automate(a);

    free(fichier_a_ouvrir);
    free(pmatch);
    free(regle_string);
    free(config_init);
    regfree(&preg);

    fclose(fp);
    return a;
}

automate lecture_runtime_automate(regle r){
    char* nb_iteration_max = (char*) malloc (sizeof(char) * 6);
    char* dimension_max = (char*) malloc (sizeof(char) * 6);

    printf("Bienvenue dans le générateur d'automate cellulaire !\n");
    printf("Afin de générer un automate, veuillez rentrer les paramètres suivants :\n");

    printf("Nombre d'itérations : ");
    scanf("%s", nb_iteration_max);
    while(!est_un_int(nb_iteration_max) || conversion_char_int(nb_iteration_max) < 1){
        scanf("%s", nb_iteration_max);
    }
    size_t taille = strlen(nb_iteration_max);
    nb_iteration_max = (char*) realloc (nb_iteration_max, sizeof(char) * taille + 1);
    nb_iteration_max[taille] = '\0';
    unsigned int nb_iteration_max_int = conversion_char_int(nb_iteration_max);

    printf("Dimension maximale : ");
    scanf("%s", dimension_max);
    while(!est_un_int(dimension_max) || conversion_char_int(dimension_max) < 1){
        scanf("%s", dimension_max);
    }
    taille = strlen(dimension_max);
    dimension_max = (char*) realloc (dimension_max, sizeof(char) * taille + 1);
    dimension_max[taille] = '\0';
    unsigned int dimension_max_int = conversion_char_int(dimension_max);

    char configuration_initiale[dimension_max_int];
    char* _regle = (char*) malloc (sizeof(char) * 15);
    char* nb_etats = (char*) malloc (sizeof(char) * 15);
    char* type_affichage = (char*) malloc (sizeof(char) * 15);
    char* type_regle = (char*) malloc (sizeof(char) * 1 + 1);

    printf("Type règle : \n");
    printf("0 - Règle binaire\n");
    printf("1 - Regle somme\n");
    printf("2 - Regle personnalisée\n");
    scanf("%s", type_regle);
    while(!est_un_int(type_regle) || (conversion_char_int(type_regle) < 0 && conversion_char_int(type_regle) > 2)){
        scanf("%s", type_regle);
    }
    taille = strlen(type_regle);
    type_regle[taille] = '\0';
    unsigned int type_regle_int = conversion_char_int(type_regle);

    unsigned int nb_etats_int;

    if(type_regle_int == 2){
        printf("Nombre d'états : \n");
        scanf("%s", nb_etats);
        while(!est_un_int(nb_etats)){
            scanf("%s", nb_etats);
        }

        taille = strlen(nb_etats);
        nb_etats = (char*) realloc (nb_etats, sizeof(char) * taille + 1);
        nb_etats[taille] = '\0';
        nb_etats_int = conversion_char_int(nb_etats);
    }

    switch(type_regle_int){
        case 0: {
            nb_etats_int = 2;
            break;
        }
        case 1: {
            nb_etats_int = 4;
            break;
        }
    }

    printf("Configuration initiale : ");
    scanf("%s", configuration_initiale);
    while(!est_regle_correcte(configuration_initiale, nb_etats_int) || strlen(configuration_initiale) != dimension_max_int){
        printf("\nVous devez rentrer une configuration initiale dont le nombre de cellule est égale à la dimension de l'automate !\n");
        scanf("%s", configuration_initiale);
    }

    printf("Règle : ");
    scanf("%s", _regle);
    if(type_regle_int == 0 && (conversion_char_int(_regle) < 0 || conversion_char_int(_regle) > 255)){
        scanf("%s", _regle);
    }else if(type_regle_int == 1 || type_regle_int == 2){
        while(!est_regle_correcte(_regle, nb_etats_int) || (int) strlen(_regle) != get_taille_regle(r)){
            scanf("%s", _regle);
        }   
    }
    taille = strlen(_regle);
    _regle = (char*) realloc (_regle, sizeof(char) * taille + 1);
    _regle[taille] = '\0';

    printf("Type affichage : \n");
    printf("0 - Affichage console\n");
    printf("1 - Génération d'une image ppm\n");
    scanf("%s", type_affichage);
    while(!est_un_int(type_affichage) || (conversion_char_int(type_affichage) != 0 && conversion_char_int(type_affichage) != 1)){
        scanf("%s", type_affichage);
    }
    type_affichage = (char*) realloc (type_affichage, sizeof(char) * 1 + 1);
    type_affichage[strlen(type_affichage)] = '\0';
    unsigned int type_affichage_int = conversion_char_int(type_affichage);

    automate a = creer_automate(dimension_max_int, nb_iteration_max_int);
    set_configuration_initiale(a, configuration_initiale);
    
    char* regle_en_binaire;

   if(type_regle_int == 0){
        regle_en_binaire = conversion_decimal_binaire(conversion_char_int(_regle));
        set_regle(r, regle_en_binaire);
   }else{
        set_regle(r, _regle);
   }

    set_regle_automate(a, r);
    switch(type_affichage_int){
        case 0: {
            set_affichage(a, &afficher_automate_console);
            break;
        }
        case 1: {
            set_affichage(a, &afficher_automate_pgm);
            break;
        }
    }

    generer_automate(a);

    free(_regle);
    _regle = NULL;
    free(type_regle);
    type_regle = NULL;
    free(regle_en_binaire);
    regle_en_binaire = NULL;
    free(dimension_max);
    dimension_max = NULL;
    free(nb_iteration_max);
    nb_iteration_max = NULL;
    free(type_affichage);
    type_affichage = NULL;
    free(nb_etats);
    nb_etats = NULL;

    return a;
}

automate process_args(regle r,int argc, char* argv[]){
    unsigned int nb_iterations = 0;
    unsigned int dimension = 0;
    unsigned int nb_etats=0;
    int type_regle =-1;

    char* regle_string = NULL;
    
    char* config_init = NULL;
    void (*type_affichage)(automate) = NULL;


    if(argc==8){
        if(!strcmp(argv[6],"0")){
            set_type_regle(r, &regle_binaire);
            set_taille_regle(r, 8);
            set_affichage_regle(r, &afficher_cellule_binaire);
            nb_etats=2;
            type_regle=0;
        }else if(!strcmp(argv[6],"1")){
            set_type_regle(r, &regle_somme);
            set_taille_regle(r, 10);
            set_affichage_regle(r, &afficher_cellule_somme);
            nb_etats=4;
            type_regle=1;
        }else{
            printf("Erreur de l'argument type_regle. Arrêt du programme");
            exit(1);
        }
    }else{
        if(!est_un_int(argv[8]) || conversion_char_int(argv[8])>9){
            printf("Erreur de l'argument nb_etats : Arrêt du programme ! \n");
            exit(1);
        }else{
            nb_etats=(unsigned int)conversion_char_int(argv[8]);
            type_regle=2;
        }
    }


    if (!est_un_int(argv[2])){
        printf("Erreur de l'argument nb_iteration : Arrêt du programme ! \n");
        exit(1);
    }else{
        nb_iterations=conversion_char_int(argv[2]);
    }


    if (!est_un_int(argv[3])){
        printf("Erreur de l'argument dimension : Arrêt du programme ! \n");
        exit(1);
    }else{
        dimension=conversion_char_int(argv[3]);
    }


    if(!est_de_longueur(argv[4],dimension)){
        printf("Erreur de l'argument dimension ou configuration : Arrêt du programme ! \n");
        exit(1);
    }else{
        if(!est_regle_correcte(argv[4],nb_etats)){
            printf("Erreur de l'argument configuration : Arrêt du programme ! \n");
            exit(1);
        }else {
        config_init=argv[4];
        }
    }

    if(type_regle==0){
        if(!est_un_int(argv[5]) ||  conversion_char_int(argv[5])<0 || conversion_char_int(argv[5])>255){
            printf("Erreur de l'argument regle pour la somme, c'est un entier qui doit etre compris enre 0 et 255");
            exit(1);
        }else{
            regle_string=conversion_decimal_binaire(conversion_char_int(argv[5]));
        }
    }else{
        if(!est_regle_correcte(argv[5],nb_etats) || !est_de_longueur(argv[5],get_taille_regle(r))){
            printf("Erreur de l'argument regle : Arrêt du programme ! \n");
            exit(1);
        }else{
            regle_string = argv[5];
        }
    }


    if(!est_un_int(argv[7]) || (strcmp(argv[7],"0") && strcmp(argv[7],"1")) ){
        printf("Erreur de l'argument type_affichage : Arrêt du programme ! \n");
        exit(1);
    }else{
        if (!strcmp(argv[7],"0")){
            type_affichage=&afficher_automate_console;
        }else{
            type_affichage=&afficher_automate_pgm;
        }
    }
    automate a ;
    a = creer_automate(dimension,nb_iterations);
    
    set_regle(r, regle_string);
    set_nb_etats(r, nb_etats);
    set_regle_automate(a, r);

    set_configuration_initiale(a, config_init);
    set_affichage(a,type_affichage);

    generer_automate(a);

    return a;
}
