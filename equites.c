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

struct t_liste_equite {
    equite* tableau;
    int nbr_case;
};

// Fonction pour analyser la valeur nette totale
liste_equite* analyse_valeur_nette_totale(equite* actifs, int nbr_actifs, equite* passifs, int nbr_passifs) {
    // Allocation de mémoire pour la liste des équités à retourner
    liste_equite* equites = (liste_equite*)malloc(sizeof(liste_equite));
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
        equites->tableau = (t_equite*)realloc(equites->tableau, (equites->nbr_case + 1) * sizeof(t_equite));
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
            equites->tableau = (t_equite*)realloc(equites->tableau, (equites->nbr_case + 1) * sizeof(t_equite));
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
    t_equite actifs[] = {
        { "A001", "Actif 1", 1000 },
        { "A002", "Actif 2", 2000 },
        // ... Ajouter plus d'actifs si nécessaire
    };
    int nbr_actifs = sizeof(actifs) / sizeof(t_equite);

    // Exemple de données pour les passifs
    t_equite passifs[] = {
        { "P001", "Passif 1", 500 },
        { "A002", "Actif 2", 1000 }, // Passif lié à un actif
        // ... Ajouter plus de passifs si nécessaire
    };
    int nbr_passifs = sizeof(passifs) / sizeof(t_equite);

    // Appel de la fonction d'analyse
    liste_equite* equites = analyse_valeur_nette_totale(actifs, nbr_actifs, passifs, nbr_passifs);

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

// Fonction pour compter le nombre de cases dans la liste d'équites
int nb_equites(Equite* liste) {
    int count = 0;
    Equite* courant = liste;

    while (courant != NULL) {
        count++;
        courant = courant->suivant;
    }

    return count;
}

// Procédure de test pour vérifier la fonction nb_equites
void tester_nb_equites() {
    // Création d'une liste d'équites pour les tests
    Equite* equite1 = (Equite*)malloc(sizeof(Equite));
    Equite* equite2 = (Equite*)malloc(sizeof(Equite));
    Equite* equite3 = (Equite*)malloc(sizeof(Equite));

    equite1->id = 1;
    equite2->id = 2;
    equite3->id = 3;

    // Liaison des équites pour former une liste
    equite1->suivant = equite2;
    equite2->suivant = equite3;
    equite3->suivant = NULL;

    // Appel de la fonction à tester
    int result = nb_equites(equite1);

    // Affichage du résultat
    printf("Nombre d'equites : %d\n", result);

    // Libération de la mémoire allouée pour les équites
    free(equite1);
    free(equite2);
    free(equite3);
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
        fprintf(fichier, "%s\t%s\t%.2f\n", liste->tableau[i].cle_unique, liste->tableau[i].description, liste->tableau[i].val_net);
    }

    // Fermeture du fichier
    fclose(fichier);
}

void test_enregistrer_analyser_valeur_nette() {
    // Création d'un exemple de liste d'équités
    equite eq1 = { "EQ001", "Equité 1", 1500.0 };
    equite eq2 = { "EQ002", "Equité 2", 2200.0 };
    equite eq3 = { "EQ003", "Equité 3", 1800.0 };
    equite eq4 = { "EQ004", "Equité 4", 3000.0 };

    liste_equite liste_eq;
    liste_eq.nbr_case = 4;
    liste_eq.tableau = (equite*)malloc(liste_eq.nbr_case * sizeof(equite));
    
    if (liste_eq.tableau == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour la liste d'équités\n");
        return;
    }

    liste_eq.tableau[0] = eq1;
    liste_eq.tableau[1] = eq2;
    liste_eq.tableau[2] = eq3;
    liste_eq.tableau[3] = eq4;

    // Appel de la fonction pour enregistrer les résultats dans un fichier
    enregistrer_analyser_valeur_nette(&liste_eq, "resultats_equites.txt");

    // Libération de la mémoire allouée pour la liste d'équités
    free(liste_eq.tableau);
}
// Fonction pour obtenir la valeur nette d'une équité spécifique
double obtenir_valeur_nette_equite(t_liste_equite* equites, int indice) {
    if (indice < 0 || indice >= equites->nombre_equites) {
        fprintf(stderr, "Indice d'équité invalide\n");
        exit(EXIT_FAILURE);
    }
    return equites->tableau[indice].val_net;
}
// Fonction de test pour obtenir la valeur nette d'une équité spécifique
void tester_obtenir_valeur_nette_equite(t_liste_equite* equites, int indice) {
    double valeur_nette = obtenir_valeur_nette_equite(equites, indice);
    printf("Valeur nette de l'équité à l'indice %d : %.2f\n", indice, valeur_nette);
}
int nb_equites(t_liste_equite* equites) {
    return equites->nombre_equites;
}

// Fonction de test pour obtenir le nombre d'équités dans la liste
void tester_nb_equites(t_liste_equite* equites) {
    int nombre_equites = nb_equites(equites);
    printf("Nombre d'équités : %d\n", nombre_equites);
}

// Fonction pour obtenir la valeur nette totale de toutes les équités
double obtenir_valeur_nette_totale(t_liste_equite* equites) {
    double somme = 0.0;
    for (int i = 0; i < equites->nbr_case; i++) {
        somme += equites->tableau[i].val_net;
    }
    return somme;
}
// Fonction de test pour obtenir la valeur nette totale
void tester_obtenir_valeur_nette_totale(t_liste_equite* equites) {
    double valeur_nette_totale = obtenir_valeur_nette_totale(equites);
    printf("Valeur nette totale : %.2f\n", valeur_nette_totale);
void test_module_equite()
{
    
}
