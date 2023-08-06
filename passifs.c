#include "passifs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Declaration de la structure encapsulee par liste_passif
struct t_passifs{
    char id[6];
    char description[51];
    double solde;
} ;

//Declaration de la structure non-encapsulee
struct t_liste_passifs{
    passifs* passifs;
    int  nombre_passifs;
} ;

// Fonction pour charger les passifs à partir du fichier
liste_passifs* charger_passif(const char* nom_fichier) {
    FILE* fichier = fopen("liste_passifs.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    // Allocation dynamique pour la structure de liste de passifs
    liste_passifs* liste = (liste_passifs*)malloc(sizeof(liste_passifs));
    if (liste == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la liste.\n");
        fclose(fichier);
        return NULL;
    }

    // Lecture du nombre de passifs
    fscanf(fichier, "nb passifs : %d", &liste->nombre_passifs);
    fgetc(fichier); // Pour consommer le caractère '\n' restant sur la première ligne

    // Allocation dynamique pour le tableau de passifs
    liste->passifs = (passifs*)malloc(liste->nombre_passifs * sizeof(passifs));
    if (liste->passifs == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour les passifs.\n");
        free(liste);
        fclose(fichier);
        return NULL;
    }

    // Lecture des données pour chaque passif
    for (int i = 0; i < liste->nombre_passifs; i++) {
        fscanf(fichier, "%5[^,],%50[^,],%lf", liste->passifs[i].id,
               liste->passifs[i].description, &liste->passifs[i].solde);
        fgetc(fichier); // Pour consommer le caractère '\n' restant sur la ligne
    }

    fclose(fichier);
    return liste;
}



//Fonction qui obtient le numero d'identification du passif choisi par l'indice
char* obtenir_id_passif(liste_passifs* liste, int indice_ele_id){

    if (liste == NULL || indice_ele_id < 0 || indice_ele_id >= liste-> nombre_passifs){
        return 0;
    }

    return liste->passifs[indice_ele_id].id;

}

// printf("Test no 3 - obtenir_id_passif()\n \t Valeur attendue: %s \n \t Valeur obtenue: p3 \n", obtenir_id_passif(liste, 8));


//Fonction qui obtient la description du passif choisi par l'indice
char* obtenir_description_passif(liste_passifs* liste, int indice_ele_desc){

    if (liste == NULL || indice_ele_desc < 0 || indice_ele_desc >= liste-> nombre_passifs){
        return 0;
    }

    return liste->passifs[indice_ele_desc].description;

}

//Fonction qui obtient le solde du passif choisi par l'indice
double obtenir_solde_passif(liste_passifs* liste, int indice_ele_solde){

    if (liste == NULL || indice_ele_solde < 0 || indice_ele_solde >= liste-> nombre_passifs){
        return 0;
    }

    return liste->passifs[indice_ele_solde].solde;

}

// Fonction pour trouver l'indice du passif avec l'id donné dans la liste
int trouver_indice_passif(const liste_passifs* liste, const char* id_passif) {
    for (int i = 0; i < liste->nombre_passifs; i++) {
        if (strcmp(liste->passifs[i].id, id_passif) == 0) {
            return i; // Indice trouvé
        }
    }
    return -1; // Indice non trouvé (valeur -1 indique l'absence du passif dans la liste)
}

// Fonction pour libérer la mémoire occupée par la liste de passifs
void detruire_liste_passif(liste_passifs* liste) {
    free(liste->passifs);
    liste->passifs = NULL;
    liste->nombre_passifs = 0;
    free(liste);
}

//Fonction pour modifier le solde du passif a partir du main
void modifier_solde_passif(liste_passifs* liste, int indice, double nouv_val){

    liste->passifs[indice].solde = nouv_val;
}











