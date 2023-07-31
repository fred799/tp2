#include "actifs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct t_actifs{
    char id[6];
    int annee;
    char description[51];
    double valeur_init;
    double pourcent_app;
    int typ_app;
    int nbr_passifs;
    char** passifs_lies;
};


 struct t_liste_actifs{
    actifs* tableau;
    int nombre_cases;
} ;





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