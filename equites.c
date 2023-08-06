#include "equite.h"
#include "actifs.c"
#include "passifs.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct t_equite {
    char id[6];
    char description[50];
    double val_net;
};

struct t_liste_equite {
    equite* tableau;
    int nbr_case;
};

//Fonction qui obtient la valeur nette d'un actif
static double valeur_nette_actif(liste_actifs* liste_actifs, int indice, liste_passifs* liste_passifs){

    double valeur_nette;
    double valeur_actif;
    double valeur_passif;

    valeur_actif = liste_actifs->tableau[indice].valeur_init;
    valeur_passif = liste_passifs->passifs[indice].solde;

    valeur_nette = valeur_actif - valeur_passif;

    return valeur_nette;
}

// Fonction pour analyser la valeur nette totale
liste_equite* analyse_valeur_nette_totale(liste_actifs* actifs, liste_passifs* passifs) {

    int nbr_actifs = actifs->nombre_cases;
    int nbr_passifs = passifs->nombre_passifs;

    // Allocation de mémoire pour la liste des équités à retourner
    liste_equite* equites = (liste_equite*)malloc(sizeof(equite));
    if (equites == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Initialisation de la liste des équités
    equites->tableau = NULL;
    equites->nbr_case = 0;

    // Traitement des actifs
    for (int i = 0; i < nbr_actifs; i++) {
        // Calcul de la valeur nette de l'actif courant
        double valeur_net_actif = actifs->tableau[i].valeur_init;

        // Ajout de l'équité représentant cet actif à la liste des équités
        equites->tableau = (liste_equite*)realloc(equites->tableau, (equites->nbr_case + 1) * sizeof(equite));

        if (equites->tableau == NULL) {
            perror("Erreur d'allocation de mémoire");
            exit(EXIT_FAILURE);
        }

        strcpy(equites->tableau[equites->nbr_case].id, actifs->tableau[i].id);
        strcpy(equites->tableau[equites->nbr_case].description, actifs->tableau[i].description);
        equites->tableau[equites->nbr_case].val_net = valeur_net_actif;

        equites->nbr_case++;
    }

    // Traitement des passifs n'étant pas liés à un actif
    for (int i = 0; i < nbr_passifs; i++) {
        int lien_actif_trouve = 0;

        // Vérifier si le passif actuel est lié à un actif
        for (int j = 0; j < nbr_actifs; j++) {
            if (strcmp(passifs->passifs[i].id, actifs->tableau[j].id) == 0) {
                lien_actif_trouve = 1;
                break;
            }
        }

        // Si le passif actuel n'est pas lié à un actif, l'ajouter à la liste des équités
        if (!lien_actif_trouve) {
            equites->tableau = (liste_equite*)realloc(equites->tableau, (equites->nbr_case + 1) * sizeof(equite));
            if (equites->tableau == NULL) {
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }

            strcpy(equites->tableau[equites->nbr_case].id, passifs->passifs[i].id);
            strcpy(equites->tableau[equites->nbr_case].description, passifs->passifs[i].description);
            equites->tableau[equites->nbr_case].val_net = -passifs->passifs[i].solde; // Passif réduit la valeur nette

            equites->nbr_case++;
        }
    }

    return equites;
}

//Fonction qui obtient le numero d'identification de l'equite
char* obtenir_id_equite(liste_actifs* liste_actifs, int indice_equ){

    return liste_actifs->tableau[indice_equ].id;

}

//Fonction qui obtient la description de l'equite
char* obtenir_description_equite(liste_actifs* liste_actifs, int indice_equ){

    return liste_actifs->tableau[indice_equ].description;

}

//Fonction qui obtient la valeur nette de l'equite
char* obtenir_valeur_nette_equite(liste_actifs* liste_actifs, int indice_equ){

    return liste_actifs->tableau[indice_equ].description;

}


// Fonction pour compter le nombre de cases dans la liste d'équites
int nb_equites(liste_equite * liste) {
    int count = 0;
    equite* courant = liste;

    while (courant != NULL) {
        count++;
        courant = courant->suivant;
    }

    return count;
}

//Fonction qui permet d'avoir la valeur nette totale des equites
double obtenir_valeur_nette_totale(liste_equite* liste){

    double total = 0;
    for(int i = 0; i < liste->nbr_case; i++){
        total += liste->tableau->val_net;
    }
    return total;
}


void enregistrer_analyser_valeur_nette(liste_equite* liste, const char* nom_fichier) {
    // Ouverture du fichier en écriture
    FILE* fichier = fopen(nom_fichier, "w");

    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }

    // Écriture de la valeur nette totale sur la première ligne
    double valeur_totale = 0.0;
    for (int i = 0; i < liste->nbr_case; i++) {
        valeur_totale += liste->tableau[i].val_net;
    }
    fprintf(fichier, "Valeur nette totale: %.2f\n", valeur_totale);

    // Écriture de l'entête sur la troisième ligne
    fprintf(fichier, "ID\tDescription\tValeur\n");

    // Écriture des équités sur les lignes subséquentes
    for (int i = 0; i < liste->nbr_case; i++) {
        fprintf(fichier, "%s\t%s\t%.2f\n", liste->tableau[i].id, liste->tableau[i].description, liste->tableau[i].val_net);
    }

    // Fermeture du fichier
    fclose(fichier);
}







