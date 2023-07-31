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
    t_passif *passifs;
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

#endif // PASSIFS_H





