

struct automate {
    int temps ; // le temps t actuelle, commence à 0
    char ** configuration_actuelle ; //chauqe char est un etat
    int regle ; // la regle a appliquer  (00011110) 2 = 30 || 0013100132 pour la somme 
    int nombre_etats ; //pas sûr wolfran =2(0,1) ; somme = 4(0,1,2,3)
    //comment définir le types de transition a effectuer ? somme || configuration des voisins ?
};