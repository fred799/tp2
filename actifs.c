#include "actifs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define anne_actuelle 2023

struct t_actifs{
    char id[6];
    int annee;
    char description[51];
    double valeur_init;
    double pourcentage;
    int type;
    int nbr_passifs;
    char** passifs_lies;
};


 struct t_liste_actifs{
    actifs* tableau;
    int nombre_cases;
} ;



// Fonction pour compter le nombre d'éléments actifs dans la liste
int nb_actif(liste_actifs *liste_actifs[], int taille) {
    int nb_elements_actifs = 0;

    for (int i = 0; i < taille; i++) {
        if (liste_actifs[i] != NULL) {
            nb_elements_actifs++;
        }
    }

    return nb_elements_actifs;
}



//Fonction qui permet de charger les les actifs a partir du fichier .txt
liste_actifs* charger_actif(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    // Lecture du nombre d'actifs inscrits dans le fichier
    int nb_actifs;
    fscanf(fichier, "nb actifs : %d\n", &nb_actifs);

    // Création du tableau dynamique pour stocker les actifs
    liste_actifs* liste_actifs = (liste_actifs*)malloc(nb_actifs * sizeof(Actif));

    // Chargement des données depuis le fichier dans le tableau
    for (int i = 0; i < nb_actifs; i++) {
        fscanf(fichier, "%[^,],%[^,],%[^,],%lf,%lf,%d,%[^\n]\n",
               liste_actifs[i].tableau->id,
               liste_actifs[i].tableau->annee,
               liste_actifs[i].tableau->description,
               &liste_actifs[i].tableau->valeur_init,
               &liste_actifs[i].tableau->pourcentage,
               &liste_actifs[i].tableau->type,
               liste_actifs[i].tableau->passifs_lies
        );
    }

    fclose(fichier);
    return liste_actifs;
}







//Fonction qui obtient l'identite de l'actif desire
char* obtenir_id_actif(liste_actifs* liste, int indice_ele_id){

    if (liste == NULL || indice_ele_id < 0 || indice_ele_id >= liste->nombre_cases){
        return 0;
    }

    return liste->tableau[indice_ele_id].id;

}

//Fonction qui obtient la description de l'actif desire
char* obtenir_description_actif(liste_actifs* liste, int indice_ele_desc){

    if (liste == NULL || indice_ele_desc < 0 || indice_ele_desc >= liste->nombre_cases){
        return 0;
    }
    return liste->tableau[indice_ele_desc].description;

}


// Fonction pour trouver l'indice de l'actif avec l'id donné dans la liste
int trouver_indice_actif(const liste_actifs* liste, const char* id_actif) {
    for (int i = 0; i < liste->nombre_cases; i++) {
        if (strcmp(liste->tableau[i].id, id_actif) == 0) {
            return i; // Indice trouvé
        }
    }
    return -1; // Indice non trouvé (valeur -1 indique l'absence de l'actif dans la liste)
}

// Fonction pour libérer la mémoire occupée par la liste d'actifs
void detruire_liste_actif(liste_actifs* liste) {
    for (int i = 0; i < liste->nombre_cases; i++) {
        for (int j = 0; j < liste->tableau[i].nbr_passifs; j++) {
            free(liste->tableau[i].passifs_lies[j]);
        }
        free(liste->tableau[i].passifs_lies);
    }
    free(liste->tableau);
    liste->tableau = NULL;
    liste->nombre_cases = 0;
    free(liste);
}


void charger_passifs_lies(liste_actifs* liste, int indice_actif){

    int nb_passifs = 0;
    int indice = indice_actif + 2;
    char* token;

    actifs* actifs = &(liste->tableau[indice]);

    actifs->passifs_lies = (char**)malloc(sizeof(char*));

    token = strtok(NULL, ",");

    if(token == NULL){
        return;
    }

    while(token != NULL){
        nb_passifs++;

        actifs->passifs_lies = (char**)realloc(actifs->passifs_lies, nb_passifs * sizeof(char*));

        actifs->passifs_lies[nb_passifs - 1] = (char*)malloc(strlen(token) + 1);
        strcpy(actifs->passifs_lies[nb_passifs - 1], token);



        token = strtok(NULL, ",");
    }

    actifs->nbr_passifs = nb_passifs;
}


char** obtenir_passifs_lies(liste_actifs* liste_actifs, int indice_actif, int* nb_passifs_lies) {

    // Vérifier si l'indice_actif est valide
    if (indice_actif < 0 || indice_actif >= *nb_actifs) {
        fprintf(stderr, "Indice d'actif invalide.\n");
        *nb_passifs_lies = 0;
        return NULL;
    }

    // Récupérer l'actif ciblé par l'indice
    actifs* actif = liste_actifs[indice_actif];

    // Compter le nombre de passifs liés
    int nb_passifs = 0;
    for (int i = 0; i < actif_cible.nbPassifsLies; i++) {
        if (actif_cible.PassifsLies[i] != NULL) {
            nb_passifs++;
        }
    }

    // Allouer de la mémoire pour le tableau 2D des ID des passifs liés
    char** passifs_lies = (char**)malloc(nb_passifs * sizeof(char*));

    // Remplir le tableau 2D avec les ID des passifs liés
    int index = 0;
    for (int i = 0; i < actif_cible.nbPassifsLies; i++) {
        if (actif_cible.PassifsLies[i] != NULL) {
            passifs_lies[index] = strdup(actif_cible.PassifsLies[i]);
            index++;
        }
    }

    // Écrire le nombre de passifs liés dans la référence passée en paramètre
    *nb_passifs_lies = nb_passifs;

    return passifs_lies;
}


//Fonction qui calcul l'appreciatiom ou depreciation de l'actif
double apprecier_deprecier_actif(liste_actifs* liste,int indice){

    //Initialisation des variables utilisees
    int age_actif;
    int valeur = liste->tableau[indice].valeur_init;

    //Calcul de l'age de l'actif
    age_actif = liste->tableau[indice].annee - anne_actuelle;

    //Aucune appreciation ou depreciation
    if(liste->tableau[indice].type == 1 || liste->tableau[indice].annee == anne_actuelle){

        return valeur;
    }

        //Appreciation de maniere lineaire
    else if(liste->tableau[indice].type == 2){

        valeur = valeur * (1 + liste->tableau[indice].pourcentage * age_actif);
        return valeur;
    }

        //Appreciation de maniere exponentielle
    else if(liste->tableau[indice].type == 3){

        valeur = valeur * pow((1 + liste->tableau[indice].pourcentage), age_actif);
        return valeur;
    }

        //Depreciation de maniere lineaire
    else if(liste->tableau[indice].type == 4){

        valeur = valeur * (1 - liste->tableau[indice].pourcentage * age_actif);
        return valeur;
    }

        //Depreciation de maniere exponentielle
    else if(liste->tableau[indice].type == 5){

        valeur = valeur * pow((1 - liste->tableau[indice].pourcentage), age_actif);
        return valeur;
    }

}


float valeur_passifs_lier_actif(liste_actifs* actifs, int indice_actif) {
    float somme_passifs = 0.0;

    // Vérification des paramètres
    if (actifs == NULL || indice_actif < 0) {
        printf("Erreur: Paramètres invalides.\n");
        return somme_passifs;
    }

    // Vérification que l'indice de l'actif est valide
    if (indice_actif >= actifs->nb_passifs) {
        printf("Erreur: Indice de l'actif invalide.\n");
        return somme_passifs;
    }

    // Récupération de l'actif à analyser
    Actif actif_analyser = actifs[indice_actif];

    // Parcours des passifs reliés à l'actif
    for (int i = 0; i < actif_analyser.nb_passifs; i++) {
        // Recherche de l'indice du passif en fonction de sa description
        int indice_passif = -1;
        for (int j = 0; j < actif_analyser.nb_passifs; j++) {
            if (strcmp(actif_analyser.passifs[j].description, actif_analyser.passifs[i].description) == 0) {
                indice_passif = j;
                break;
            }
        }

        // Si l'indice du passif est trouvé, on accumule sa valeur dans la somme
        if (indice_passif != -1) {
            somme_passifs += actif_analyser.passifs[indice_passif].valeur;
        }
    }

    return somme_passifs;
}


//Fonction qui verifie si un passif est bien lie a un actif
int passif_est_lier_a_actif(liste_actifs* liste, const char* id){
    int valeur = 0;

    for(int i = 0; i <  liste->nombre_cases; i++){

        if (liste->tableau[i].nbr_passifs > 0) {

            for(int j = 0; j < liste->tableau->nbr_passifs; j++){

                if(strcmp(liste->tableau[i].passifs_lies[j], id) == 0){
                    valeur = 1;
                }
            }

        }

    }


    return valeur;
}




//Fonction pour modifier le solde de l'actif a partir du main
void modifier_solde_actif(liste_actifs* liste, int indice, double nouv_val){

    liste->tableau[indice].valeur_init = nouv_val;
}














