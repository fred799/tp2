#include "equites.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "actifs.h"
#include "passifs.h"

struct t_equite {
    char cle_unique[6];
    char description[50];
    double val_net;
};

struct liste_equite {
    equite* tableau;
    int nbr_case;
};

// Fonction pour analyser la valeur nette totale
liste_equite* analyse_valeur_nette_totale(equite* actifs, int nbr_actifs, equite* passifs, int nbr_passifs) {
    // Allocation de mémoire pour la liste des équités à retourner
    struct liste_equite* equites = (struct liste_equite*)malloc(sizeof(struct liste_equite));
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
        double valeur_net_actif = actifs[i].val_net;

        // Ajout de l'équité représentant cet actif à la liste des équités
        equites->tableau = (struct t_equite*)realloc(equites->tableau, (equites->nbr_case + 1) * sizeof(struct t_equite));
        if (equites->tableau == NULL) {
            perror("Erreur d'allocation de mémoire");
            exit(EXIT_FAILURE);
        }

        strcpy(equites->tableau[equites->nbr_case].cle_unique, actifs[i].cle_unique);
        strcpy(equites->tableau[equites->nbr_case].description, actifs[i].description);
        equites->tableau[equites->nbr_case].val_net = valeur_net_actif;

        equites->nbr_case++;
    }

    // Traitement des passifs n'étant pas liés à un actif
    for (int i = 0; i < nbr_passifs; i++) {
        int lien_actif_trouve = 0;

        // Vérifier si le passif actuel est lié à un actif
        for (int j = 0; j < nbr_actifs; j++) {
            if (strcmp(passifs[i].cle_unique, actifs[j].cle_unique) == 0) {
                lien_actif_trouve = 1;
                break;
            }
        }

        // Si le passif actuel n'est pas lié à un actif, l'ajouter à la liste des équités
        if (!lien_actif_trouve) {
            equites->tableau = (struct t_equite*)realloc(equites->tableau, (equites->nbr_case + 1) * sizeof(struct t_equite));
            if (equites->tableau == NULL) {
                perror("Erreur d'allocation de mémoire");
                exit(EXIT_FAILURE);
            }

            strcpy(equites->tableau[equites->nbr_case].cle_unique, passifs[i].cle_unique);
            strcpy(equites->tableau[equites->nbr_case].description, passifs[i].description);
            equites->tableau[equites->nbr_case].val_net = -passifs[i].val_net; // Passif réduit la valeur nette

            equites->nbr_case++;
        }
    }

    return equites;
}

// Procédure de test
void test_analyse_valeur_nette_totale() {
    // Exemple de données pour les actifs
    struct t_equite actifs[] = {
        { "A001", "Actif 1", 1000 },
        { "A002", "Actif 2", 2000 },
        // ... Ajouter plus d'actifs si nécessaire
    };
    int nbr_actifs = sizeof(actifs) / sizeof(struct t_equite);

    // Exemple de données pour les passifs
    struct t_equite passifs[] = {
        { "P001", "Passif 1", 500 },
        { "A002", "Actif 2", 1000 }, // Passif lié à un actif
        // ... Ajouter plus de passifs si nécessaire
    };
    int nbr_passifs = sizeof(passifs) / sizeof(struct t_equite);

    // Appel de la fonction d'analyse
    struct liste_equite* equites = analyse_valeur_nette_totale(actifs, nbr_actifs, passifs, nbr_passifs);

    // Affichage des équités résultantes
    printf("Liste des équités :\n");
    for (int i = 0; i < equites->nbr_case; i++) {
        printf("Cle unique : %s, Description : %s, Valeur nette : %.2f\n",
               equites->tableau[i].cle_unique, equites->tableau[i].description, equites->tableau[i].val_net);
    }

    // Libération de la mémoire
    free(equites->tableau);
    free(equites);
}
