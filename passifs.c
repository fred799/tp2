#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "passifs.h"

// Définition de la structure t_passif
struct t_passif{
    char id[6];
    char description[51];
    float solde;
};

// Définition de la structure t_liste_passif
struct t_liste_passif
{
    passif *passifs;
    int nombre_passifs;
};


// Fonction qui compte le nombre d'éléments passifs dans une liste
int nb_passif(liste_passif* liste_passifs)
{
    // Vérification des cas spéciaux
    if (liste_passif == NULL || liste_passif->elements == NULL || liste_passif->nb_elements <= 0) {
        return 0;
    }

    // Comptage du nombre d'éléments passifs
    int count = 0;
    for (int i = 0; i < liste_passif->nb_elements; i++) {
        // Vérifier ici si l'élément à l'index i est un élément passif valide
        // Si oui, incrémenter le compteur
        // Exemple : if (valider_element_passif(liste->elements[i]))
        count++;
    }

    return count;
}

// Procédure de test pour la fonction nb_passif
void tester_nb_passif() {
    // Création d'une liste de passifs pour les tests
    passif* passifs_test[] = {
            // Initialiser ici les éléments passifs pour les tests
            // Exemple : { "Passif 1", "Description du passif 1" },
            //           { "Passif 2", "Description du passif 2" },
    };

    liste_passif liste_test;
    liste_test.elements = passifs_test;
    liste_test.nb_elements = sizeof(passifs_test) / sizeof(passifs_test[0]);

    // Appel de la fonction à tester
    int resultat = nb_passif(&liste_test);

    // Affichage du résultat des tests
    printf("Nombre d'éléments passifs : %d\n", resultat);
}

// Fonction pour charger les passifs à partir du fichier
ListePassifs* charger_passif(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    ListePassifs* liste = (ListePassifs*)malloc(sizeof(ListePassifs));
    if (liste == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la liste.\n");
        fclose(fichier);
        return NULL;
    }

    // Lecture du nombre de passifs
    fscanf(fichier, "nb passifs : %d", &liste->nb_passifs);
    fgetc(fichier); // Pour consommer le caractère '\n' restant sur la première ligne

    // Allocation dynamique pour le tableau de passifs
    liste->passifs = (Passif*)malloc(liste->nb_passifs * sizeof(Passif));
    if (liste->passifs == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour les passifs.\n");
        free(liste);
        fclose(fichier);
        return NULL;
    }

    // Lecture des données pour chaque passif
    for (int i = 0; i < liste->nb_passifs; i++) {
        fscanf(fichier, "%9[^,],%49[^,],%lf", liste->passifs[i].ID,
               liste->passifs[i].Description, &liste->passifs[i].Solde);
        fgetc(fichier); // Pour consommer le caractère '\n' restant sur la ligne
    }

    fclose(fichier);
    return liste;
}


// Procédure de test pour afficher les passifs
void tester_charger_passif() {
    const char* nom_fichier = "liste_passifs.txt";
    ListePassifs* liste = charger_passif(nom_fichier);
    if (liste != NULL) {
        printf("Nombre de passifs : %d\n", liste->nb_passifs);
        for (int i = 0; i < liste->nb_passifs; i++) {
            printf("ID: %s, Description: %s, Solde: %.2f\n",
                   liste->passifs[i].ID, liste->passifs[i].Description, liste->passifs[i].Solde);
        }

        // Libérer la mémoire allouée pour la liste de passifs
        free(liste->passifs);
        free(liste);
    }
}

// Fonction pour modifier le solde d'un passif en fonction de son indice
void modifier_solde_passif(struct t_liste_passif *liste, int indice_passif, float nouvelle_valeur) {
    if (liste == NULL || indice_passif < 0 || indice_passif >= liste->nombre_passifs) {
        printf("Erreur : Indice de passif invalide.\n");
        return;
    }

    liste->passifs[indice_passif].solde = nouvelle_valeur;
}
// Fonction pour trouver l'indice du passif avec l'id donné dans la liste
int trouver_indice_passif(const t_liste_passif* liste, const char* id_passif) {
    for (int i = 0; i < liste->nombrePassifs; i++) {
        if (strcmp(liste->tableau[i].id, id_passif) == 0) {
            return i; // Indice trouvé
        }
    }
    return -1; // Indice non trouvé (valeur -1 indique l'absence du passif dans la liste)
}

 

// Fonction pour libérer la mémoire occupée par la liste de passifs
void detruire_liste_passif(t_liste_passif* liste) {
    free(liste->tableau);
    liste->tableau = NULL;
    liste->nombrePassifs = 0;
    free(liste);
}

 

// Procédure de test pour la fonction modifier_solde_passif
void test_modifier_solde_passif() {
    // Création de la liste de passifs de test
    struct t_passif passifs_test[] = {
        {"P001", "Passif 1", 1000.0},
        {"P002", "Passif 2", 1500.0},
        {"P003", "Passif 3", 2000.0},
        // Vous pouvez ajouter plus de passifs de test ici si nécessaire
    };
    int nombre_passifs_test = sizeof(passifs_test) / sizeof(passifs_test[0]);

    struct t_liste_passif liste_test;
    liste_test.passifs = passifs_test;
    liste_test.nombre_passifs = nombre_passifs_test;

    // Affichage des passifs avant modification
    printf("Passifs avant modification :\n");
    for (int i = 0; i < liste_test.nombre_passifs; i++) {
        printf("ID: %s, Description: %s, Solde: %.2f\n",
               liste_test.passifs[i].id,
               liste_test.passifs[i].description,
               liste_test.passifs[i].solde);
    }

    // Test de la fonction modifier_solde_passif pour modifier le passif à l'indice 1
    int indice_passif_a_modifier = 1;
    float nouvelle_valeur_passif = 1800.0;
    modifier_solde_passif(&liste_test, indice_passif_a_modifier, nouvelle_valeur_passif);

    // Affichage des passifs après modification
    printf("\nPassifs après modification :\n");
    for (int i = 0; i < liste_test.nombre_passifs; i++) {
        printf("ID: %s, Description: %s, Solde: %.2f\n",
               liste_test.passifs[i].id,
               liste_test.passifs[i].description,
               liste_test.passifs[i].solde);
    }
}

void test_module_passifs()
{
    
}





