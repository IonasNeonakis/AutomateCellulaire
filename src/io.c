
/**
 * \file io.c
 * \brief Fichier se rapportant à la gestion des différentes méthodes de création d'un automate
 * \author Ionas Samir
 *
 */

#include "../include/affichage.h"
#include "../include/io.h"

/**
 * \fn automate lire_fichier_automate(automate, regle, char*)
 * \brief Fonction permettant de générer un automate à partir d'une configuration dans un fichier
 * \author Ionas
 * 
 * Le fichier va être lu en agrémentant l'automate au fur et à mesure des différents paramètres de configuration écrits dans le fichier
 * Afin que l'automate puisse se générer correctement, il est nécessaire que le fichier respecte les règles décrites dans le manuel.
 * 
 * \param automate automate_cellulaire représente l'automate sur lequel la fonction va opérer
 * \regle r représente la règle personnalisé si elle existe
 * \char* nom_fichier représente le nom du fichier de configuration
 */

automate lire_fichier_automate(automate a, char* nom_fichier){
    unsigned int nb_iterations = 0;
    unsigned int dimension = 0;
    unsigned int nb_etats = 0;
    int type_regle = -1;
    char* regle_string = NULL;
    regle r = get_regle_automate(a);
    
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
    char* fichier_a_ouvrir =(char*) malloc(sizeof(char) * strlen(nom_fichier) + 1 + strlen(cfg));
    strcpy(fichier_a_ouvrir, cfg);
    strcat(fichier_a_ouvrir, nom_fichier);

    fp = fopen(fichier_a_ouvrir, "r");
    
    if (fp == NULL){
        fprintf(stderr, "Erreur lors de l'ouverture du fichier en lecture ! \n");
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

    while(fgets(chaine, 20000, fp) != NULL){

        pmatch = realloc(pmatch, sizeof(*pmatch) * nmatch);

        if (pmatch){
            match = regexec(&preg, chaine, nmatch, pmatch, 0);
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
                if(nb_iterations != 0){
                    printf("Duplication du type : \"nb_iteration\". Arrêt du programme !\n");
                    exit(1);
                }else{
                    nb_iterations = (unsigned int) conversion_char_int(valeur);
                }
            }else if(!strcmp(type, "dimension")){
                if(dimension != 0){
                    printf("Duplication du type : \"dimension\". Arrêt du programme !\n");
                    exit(1);
                }else if(config_init!=NULL && !est_de_longueur(config_init, conversion_char_int(valeur))){
                    printf("\"config_init\" doit etre de la même longueur que \"dimension\". Arrêt du programme !\n");
                    exit(1);
                }else{
                    dimension=(unsigned int) conversion_char_int(valeur);
                }
            }else if(!strcmp(type, "regle")){
                if (regle_string != NULL){
                    printf("Duplication du type : \"regle\". Arrêt du programme !\n");
                    exit(1);
                }else if(type_regle!= 0 && !est_de_longueur(valeur,get_taille_regle(r))){    
                    printf("La regle n'est pas de la bonne longueur. Arrêt du programme !\n");
                    exit(1);
                }else if(nb_etats == 0){
                    printf("\"nb_etat\" doit etre défini avant \"regle\". Arrêt du programme !\n");
                    exit(1);
                }else if(type_regle !=0 && !est_regle_correcte(valeur, nb_etats)){
                    printf("Erreur de la saisie de la regle comparé aux nombre d'états. Arrêt du programme ! \n");
                    exit(1);
                }else{
                    regle_string = (char*) calloc(strlen(valeur)+1,sizeof(char) * strlen(valeur)+1);
                    if(type_regle == 0 && (conversion_char_int(valeur) > 255 || conversion_char_int(valeur) < 0)){
                        printf("la regle binaire doit être entre 0 et 255. Arrêt du programe ! \n");
                        exit(1);
                    }else if(type_regle == 0){
                        char *tab = conversion_decimal_binaire(conversion_char_int(valeur));
                        regle_string = strcpy(regle_string, tab);
                        free(tab);
                    }else {
                        regle_string = strcpy(regle_string, valeur);
                    }
                }


            }else if(!strcmp(type, "config_init")){
               if (config_init != NULL){
                    printf("Duplication du type : \"config_init\". Arrêt du programme !\n");
                    exit(1);
                }else if(dimension != 0 && !est_de_longueur(valeur, dimension)){
                    printf("\"dimension\" doit etre de la même longuer que \"config_init\". Arrêt du programme !\n");
                    exit(1);
                }else if(nb_etats == 0){
                    printf("\"nb_etats\" doit etre défini avant \"config_init\". Arrêt du programme !\n");
                    exit(1);
                }else if(!est_regle_correcte(valeur, nb_etats)){
                    printf("Erreur de la saisie de la regle comparé aux nombre d'états. Arrêt du programme ! \n");
                    exit(1);
                }else{
                    config_init = (char*) malloc (sizeof(char) * strlen(valeur) + 1);
                    config_init = strcpy(config_init, valeur);
                }
            }else if(!strcmp(type, "nb_etats")){
                if(type_regle == 0 || type_regle == 1){
                    printf("\"nb_etats\" ne doit pas être défini si \"type_regle\" vaut 0 ou 1. Arrêt du programme ! \n");
                    exit(1);
                }else if(type_regle == -1){
                    printf("\"type_regle\" doit être défini avant \"nb_etats\". Arrêt du programme ! \n");
                    exit(1);
                }else if(nb_etats != 0){
                    printf("Duplication du type : \"nb_iteration\". Arrêt du programme !\n");
                    exit(1);
                }else if(conversion_char_int(valeur) > 9 || conversion_char_int(valeur)<1){
                    printf("\"nb_etats\" ne peut être supérieur à 9 et inférieur à 1. Arrêt du programme ! \n");
                    exit(1);
                }else{
                    nb_etats=(unsigned int) conversion_char_int(valeur);
                }
            }else if(!strcmp(type, "type_affichage")){
                if(type_regle == 2){
                    printf("\"type_affichage\" ne doit pas etre défini dans le cas ou le \"type_regle\" vaut 2 : Arrêt du programme ! \n");
                    exit(1);
                }else if(type_affichage != NULL){
                    printf("Duplication du type : \"type_affichage\". Arrêt du programme !\n");
                    exit(1);
                }else if(type_regle == -1){
                    printf("\"type_regle\" doit être défini avant \"type_affichage\" : Arrêt du programme \n");
                    exit(1);
                }else{
                    int val = conversion_char_int(valeur);
                    if (type_regle == 0){ // binaire
                        if (val == 0 ){ // console 
                            type_affichage = afficher_automate_console_binaire;
                        }else if(val == 1){ //pgm
                            type_affichage = afficher_automate_pgm_binaire;
                        }else{ // perso
                            type_affichage = get_affichage(a);
                        }
                    }else if (type_regle == 1){ //somme
                        if (val == 0 ){ // console 
                            type_affichage = afficher_automate_console_somme;               
                        }else if(val == 1){ //pgm
                            type_affichage = afficher_automate_pgm_somme;
                        }else{ // perso
                            type_affichage = get_affichage(a);
                        }
                    }else { // regle perso erreur
                        printf("Erreur inconue : Arrêt du programme ! \n");
                        exit(1);
                    }
                }
            }else if(!strcmp(type, "type_regle")){
                if(type_regle != -1){
                    printf("Duplication du type : \"type_regle\". Arrêt du programme !\n");
                    exit(1);
                }else{
                    switch (conversion_char_int(valeur)){
                        case 0: {
                            set_type_regle(r, &regle_binaire);
                            set_taille_regle(r, 8);
                            nb_etats = 2;
                            type_regle = 0;
                            break;
                        }case 1 :{
                            set_type_regle(r, &regle_somme);
                            set_taille_regle(r, 10);
                            nb_etats = 4;
                            type_regle = 1;
                            break;
                        }case 2 : {
                            type_regle = 2;
                            type_affichage = get_affichage(a);
                            break;
                        }
                        default:{
                            printf("Erreur de \"type_regle\". Arrêt du programme ! \n");
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
    if(dimension == 0 || regle_string == NULL || config_init == NULL || nb_iterations == 0 ||type_affichage == NULL || type_regle == -1 || (nb_etats == 0 && type_regle == 2)){
        printf("Fichier incomplet pour l'éxecution du programme. Arrêt du programme !\n");
        exit(1);
    }
    set_dimension_max(a, dimension);
    set_nb_iterations_max(a, nb_iterations);
    init_configuration_actuelle(a);
    set_regle(r, regle_string);
    set_nb_etats(r, nb_etats);
    set_regle_automate(a, r);

    set_configuration_initiale(a, config_init);
    set_affichage(a, type_affichage);

    generer_automate(a);

    free(fichier_a_ouvrir);
    free(pmatch);
    free(regle_string);
    free(config_init);
    regfree(&preg);

    fclose(fp);
    return a;
}

/**
 * \fn automate lecture_runtime_automate(regle r)
 * \brief Fonction permettant de lire pendant l'exécution du programme les différents paramètres de l'automate
 * \author Samir
 * 
 * La fonction va générer un automate en fonction des paramètre que l'utilisateur va rentrer au fur et à mesure de l'exécution du programme
 * 
 * \param regle r représente la regle si l'utilisateur veut utiliser une règle personnalisée
 * \return automate ainsi créé
 */
void lecture_runtime_automate(automate a){
    regle r = get_regle_automate(a);
    char* piscine_buffer = (char*) malloc (sizeof(char) * 1024);

    printf("Bienvenue dans le générateur d'automate cellulaire !\n");
    printf("Afin de générer un automate, veuillez rentrer les paramètres suivants :\n");

    printf("Nombre d'itérations : ");
    scanf("%s", piscine_buffer);
    while(!est_un_int(piscine_buffer) || conversion_char_int(piscine_buffer) < 1){
        printf("Vous devez rentrer un nombre d'itérations positif !\n");
        scanf("%s", piscine_buffer);
    }
    size_t taille = strlen(piscine_buffer);
    piscine_buffer[taille] = '\0';
    unsigned int nb_iteration_max_int = conversion_char_int(piscine_buffer);

    printf("Dimension maximale : ");
    scanf("%s", piscine_buffer);
    while(!est_un_int(piscine_buffer) || conversion_char_int(piscine_buffer) < 1){
        printf("Vous devez rentrer une dimension max positive !\n");
        scanf("%s", piscine_buffer);
    }
    taille = strlen(piscine_buffer);
    piscine_buffer[taille] = '\0';
    unsigned int dimension_max_int = conversion_char_int(piscine_buffer);

    char* configuration_initiale;;
    char* _regle;

    printf("Type règle : \n");
    printf("0 - Règle binaire\n");
    printf("1 - Regle somme\n");
    printf("2 - Regle personnalisée\n");
    scanf("%s", piscine_buffer);
    while(!est_un_int(piscine_buffer) || (conversion_char_int(piscine_buffer) < 0 || conversion_char_int(piscine_buffer) > 2)){
        printf("Vous devez entrer un entier parmis les choix disponibles (0, 1 ou 2) !\n");
        scanf("%s", piscine_buffer);
    }
    taille = strlen(piscine_buffer);
    piscine_buffer[taille] = '\0';
    unsigned int type_regle_int = conversion_char_int(piscine_buffer);

    unsigned int nb_etats_int;

    if(type_regle_int == 2){
        printf("Nombre d'états : \n");
        scanf("%s", piscine_buffer);
        while(!est_un_int(piscine_buffer) || conversion_char_int(piscine_buffer) < 1){
            printf("Vous devez entrer un nombre d'état positif !\n");
            scanf("%s", piscine_buffer);
        }

        taille = strlen(piscine_buffer);
        piscine_buffer[taille] = '\0';
        nb_etats_int = conversion_char_int(piscine_buffer);
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
    scanf("%s", piscine_buffer);
    bool correcte = est_regle_correcte(piscine_buffer, nb_etats_int);
    bool l_pas_bonne = strlen(piscine_buffer) != dimension_max_int;
    while(!correcte || l_pas_bonne){
        if(!correcte){
            printf("Vous devez rentrer une configuration intiale dont les chiffres qui la compose se situent entre 0 et le nombre d'état de la règle !\n");
        }
        if(l_pas_bonne){
            printf("\nVous devez rentrer une configuration initiale dont le nombre de cellule est égale à la dimension de l'automate !\n");
        }
        scanf("%s", piscine_buffer);
        correcte = est_regle_correcte(piscine_buffer, nb_etats_int);
        l_pas_bonne = strlen(piscine_buffer) != dimension_max_int;  
    }
    configuration_initiale = (char*) malloc(sizeof(char) * dimension_max_int + 1);
    strcpy(configuration_initiale, piscine_buffer);

    printf("Règle : ");
    scanf("%s", piscine_buffer);
    if(type_regle_int == 0){
        while (conversion_char_int(piscine_buffer) < 0 || conversion_char_int(piscine_buffer) > 255){
            printf("Vous devez rentrer un entier compris entre 0 et 255 !\n");
            scanf("%s", piscine_buffer);
        }
    }else if(type_regle_int == 1 ){ 
        while(!est_regle_correcte(piscine_buffer, nb_etats_int) || (int) strlen(piscine_buffer) != 10){
            printf("Vous devez entrer une règle comportant 10 entiers compris entre 0 et 3 !\n");
            scanf("%s", piscine_buffer);
        }
    }else if(type_regle_int == 2){
        while(!est_regle_correcte(piscine_buffer, nb_etats_int) || (int) strlen(piscine_buffer) != get_taille_regle(r)){
            printf("Vous devez entrer une règle comportant autant d'entiers que la taille de votre règle, compris entre 0 et le nombre d'états de votre règle !\n");
            scanf("%s", piscine_buffer);
        }   
    }
    taille = strlen(piscine_buffer);
    _regle = (char*) malloc (sizeof(char) * taille + 1);
    strcpy(_regle, piscine_buffer);
    _regle[taille] = '\0';

    unsigned int type_affichage_int;

    if(type_regle_int == 0 || type_regle_int == 1){
        printf("Type affichage : \n");
        printf("0 - Affichage console\n");
        printf("1 - Génération d'une image ppm\n");
        printf("2 - Utilisation de la fonction d'affichage personnalisée\n");
        scanf("%s", piscine_buffer);
        while(!est_un_int(piscine_buffer) || (conversion_char_int(piscine_buffer) < 0 || conversion_char_int(piscine_buffer) > 2)){
            printf("Vous devez entrer un entier parmis les choix disponibles (0, 1 ou 2) !\n");
            scanf("%s", piscine_buffer);
        }
        piscine_buffer[strlen(piscine_buffer)] = '\0';
        type_affichage_int = conversion_char_int(piscine_buffer);
   }else{
       type_affichage_int = 2;
   }
   
    set_dimension_max(a, dimension_max_int);

    set_nb_iterations_max(a, nb_iteration_max_int);

    init_configuration_actuelle(a);
    
    set_configuration_initiale(a, configuration_initiale);
    
    char* regle_en_binaire;

   if(type_regle_int == 0){
        regle_en_binaire = conversion_decimal_binaire(conversion_char_int(_regle));
        set_regle(r, regle_en_binaire);
        set_type_regle(r, &regle_binaire);

        free(regle_en_binaire);
        regle_en_binaire = NULL;
   }else if(type_regle_int == 1){
        set_regle(r, _regle);
        set_type_regle(r, &regle_somme);
   }else{
       set_regle(r, _regle);
   }

    set_regle_automate(a, r);
    
    if(type_regle_int == 0){
        if(type_affichage_int == 0){
            set_affichage(a, &afficher_automate_console_binaire);
        }else if(type_affichage_int == 1){
            set_affichage(a, &afficher_automate_pgm_binaire);
        }
    }else if(type_regle_int == 1){
        if(type_affichage_int == 0){
            set_affichage(a, &afficher_automate_console_somme);
        }else if(type_affichage_int == 1){
            set_affichage(a, &afficher_automate_pgm_somme);
        }
    }

    generer_automate(a);

    free(_regle);
    _regle = NULL;
    free(configuration_initiale);
    configuration_initiale = NULL;
    free(piscine_buffer);
    piscine_buffer = NULL;
}

void process_args(automate a,int argc, char* argv[]){
    unsigned int nb_iterations = 0;
    unsigned int dimension = 0;
    int type_regle = -1;

    unsigned int nb_etats = 0;
    char* regle_string = NULL;
    
    char* config_init = NULL;
    void (*type_affichage) (automate) = NULL;

    regle r = get_regle_automate(a);

    if(argc == 8){
        if(!strcmp(argv[6], "0")){
            set_type_regle(r, &regle_binaire);
            set_taille_regle(r, 8);
            nb_etats = 2;
            type_regle = 0;
        }else if(!strcmp(argv[6], "1")){
            set_type_regle(r, &regle_somme);
            set_taille_regle(r, 10);
            nb_etats = 4;
            type_regle = 1;
        }else if(!strcmp(argv[6], "2")){
            type_regle = 2;
        }
    }else{
        printf("Erreur du nombre d'argument du programme. Arrêt du programme ! \n");
        exit(1);
    }

    if(!strcmp(argv[6], "2")){
        if(!est_un_int(argv[7]) || conversion_char_int(argv[7]) > 9 || conversion_char_int(argv[7]) < 1){
            printf("Erreur de l'argument \"nb_etats\" : Arrêt du programme ! \n");
            exit(1);
        }else{
            nb_etats=(unsigned int) conversion_char_int(argv[7]);
            type_regle = 2;
            type_affichage = get_affichage(a);

        }
    }else{
        if(!est_un_int(argv[7]) || conversion_char_int(argv[7]) > 2 || conversion_char_int(argv[7]) < 0){
            printf("Erreur de l'argument \"type_affichage\"\n");
            exit(1);
        }else if (type_regle == 0){ // binaire
            if (!strcmp(argv[7], "0")){ // console
                type_affichage = &afficher_automate_console_binaire;   
            }else if (!strcmp(argv[7], "1")){ // pgm
                type_affichage = &afficher_automate_pgm_binaire;   
            }else{
                type_affichage = get_affichage(a);
            }
        }else if (type_regle == 1){ // somme
            if (!strcmp(argv[7], "0")){ // console
                type_affichage=&afficher_automate_console_somme;   
            }else if (!strcmp(argv[7], "1")){ // pgm
                type_affichage = &afficher_automate_pgm_somme;   
            }else{
                type_affichage = get_affichage(a);
            }
        }else if (type_regle == 2){ 
            printf("erreur du type de regle \n");
            exit(1);
        }
    }

    if (!est_un_int(argv[2]) || conversion_char_int(argv[2]) < 1){
        printf("Erreur de l'argument \"nb_iteration\" : Arrêt du programme ! \n");
        exit(1);
    }else{
        nb_iterations = conversion_char_int(argv[2]);
    }


    if (!est_un_int(argv[3]) || conversion_char_int(argv[3]) < 1){
        printf("Erreur de l'argument \"dimension\" : Arrêt du programme ! \n");
        exit(1);
    }else{
        dimension = conversion_char_int(argv[3]);
    }


    if(!est_de_longueur(argv[4], dimension)){
        printf("Erreur de l'argument \"dimension\" ou \"config_init\" : Arrêt du programme ! \n");
        exit(1);
    }else{
        if(!est_regle_correcte(argv[4], nb_etats)){
            printf("Erreur de l'argument \"config_init\" ou \"nb_etats\" : Arrêt du programme ! \n");
            exit(1);
        }else {
        config_init = argv[4];
        }
    }

    if(type_regle == 0){
        if(!est_un_int(argv[5]) ||  conversion_char_int(argv[5]) < 0 || conversion_char_int(argv[5]) > 255){
            printf("Erreur de l'argument regle pour Wolfram, c'est un entier qui doit etre compris enre 0 et 255 \n");
            exit(1);
        }else{
            regle_string = (char*) calloc(strlen(argv[5]) + 1, sizeof(char) * strlen(argv[5]) + 1);
            char *tab = conversion_decimal_binaire(conversion_char_int(argv[5]));
            regle_string=strcpy(regle_string, tab);
            free(tab);
        }
    }else{
        if(!est_regle_correcte(argv[5], nb_etats) || !est_de_longueur(argv[5], get_taille_regle(r))){
            printf("Erreur de l'argument \"regle\" : Arrêt du programme ! \n");
            exit(1);
        }else{
            regle_string = (char*) calloc(strlen(argv[5]) + 1, sizeof(char) * strlen(argv[5]) + 1);
            regle_string = strcpy(regle_string, argv[5]);
        }
    }

    set_dimension_max(a, dimension);
    set_nb_iterations_max(a, nb_iterations);
    init_configuration_actuelle(a);
    set_regle(r, regle_string);
    free(regle_string);
    set_nb_etats(r, nb_etats);
    set_regle_automate(a, r);

    set_configuration_initiale(a, config_init);
    set_affichage(a, type_affichage);

    generer_automate(a);
}

/**
 * \fn void manuel()
 * \brief Cette fonction affiche le manuel
 * \author Samir
 */

void manuel(){
    printf("Bienvenue dans le manuel !\n\n");
    printf("Ce programme vous permet de générer un automate cellulaire en fonction de plusieurs paramètres.\n");
    printf("Afin de correctement générer un automate, plusieurs options sont disponibles : \n\n");
    printf("Il est tout d'abord possible de générer l'automate cellulaire en utilisant un fichier de configuration, cela peut se faire en utilisant l'argument '-f' ou '--file' suivi du nom du fichier à utiliser.\n");
    printf("Ce fichier doit être placer dans le dossier 'cfg' et doit absolument respecter les modèles déjà présent dans ce dossier.\n\n");
    printf("EXEMPLE : ./automate -f nom_du_fichier.config\n\n");
    printf("NOTE : Le nombre d'état ne doit être précisé dans le cas unique où vous créez votre propre règle. Il n'est donc pas nécessaire de préciser ce nombre lors de l'utilisation de la règle de Wolfram ou Somme\n\n");
    printf("Il est également possible de générer un automate  en passant des arguments directement au programme, cela peut se faire en utilisant l'argument '-a' ou '--args' suivi des paramètres dont voici l'ordre :\n\n");
    printf("NOMBRE_ITERATIONS  DIMENSION_MAX  CONFIGURATION_INITIALE  REGLE  TYPE_REGLE  [TYPE_AFFICHAGE|NB_ETATS]\n\n");
    printf("EXEMPLE 1 : ./bin/automates -a 16 11 00000100000 30 0 1\n");
    printf("NOMBRE_ITERATIONS=16  DIMENSION_MAX=11  CONFIGURATION_INITIALE=00000100000  REGLE=30  TYPE_REGLE=0(Binaire)  TYPE_AFFICHAGE=1(Image pgm)\n\n");
    printf("EXEMPLE 2 : ./bin/automates -a 16 16 0230100104102100 234024314 2 5\n");
    printf("NOMBRE_ITERATIONS=16  DIMENSION_MAX=16  CONFIGURATION_INITIALE=0230100104102100  REGLE=234024314  TYPE_REGLE=2(Perso)  NB_ETATS=5(0 1 2 3 4)\n\n");
    printf("- Le nombre d'itération doit etre un entier positif\n");
    printf("- La dimension max doit être un entier positif\n");
    printf("- La taille de la configuration initiale doit être égale à la dimension max, et ne doit comporter que des chiffres compris entre 0 et le nombre d'états possibles\n");
    printf("- La règle somme est une succession de 10 entier compris entre 0 et 3\n");
    printf("- La règle de Wolfram est un entier compris entre 0 et 255\n\n");
    printf("NOTE : Dans le cas d'une règle personnalisée, vous devrez concevoir son implémentation ainsi que sa règle d'affichage dans le code\n\n");
    printf("- Type règle est 0 pour une règle de Wolfram, 1 pour une règle somme, 2 pour une règle personnalisée\n");
    printf("- Type affichage est 0 pour un affichage dans la console, 1 pour la génération d'une image de l'automate\n");
    printf("Nombre d'états corresponds aux états possibles pour une cellule, ce chiffre, positif, ne doit être précisé seulement dans le cas de l'utilisation d'une règle personnalisée\n\n");
    printf("Enfin, il est possible de générer un automate en utilisant la lecture runtime, c'est à dire pendant l'exécution du programme, cela se fait en ne passant aucun arguments au programme.\n");
    printf("Les règles à respecter sont identiques à celles cîtées plus haut.\n\n");
    printf("NOTE : Tant que vous ne rentrerez pas une valeur correcte vérifiant chacunes de ces règles, le programme vous redemandera la valeur.\n\n");
    printf("Merci d'avoir lu ce manuel, bon courage !\n");
}
