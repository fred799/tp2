#include "actifs.h"

// Définition de la structure t_passif
struct t_actif{
    char id[6];
    int date;
    char description[51];
    float prix_a_neuf;
    float appreciation;
    int
    int

};

// Définition de la structure t_liste_passif
struct t_liste_actif
{
    t_actif *actifs;
    int nombre_actifs;
};

// Fonction pour compter le nombre d'éléments actifs dans la liste
int nb_actif(Actif *liste_actifs[], int taille) {
    int nb_elements_actifs = 0;

    for (int i = 0; i < taille; i++) {
        if (liste_actifs[i] != NULL) {
            nb_elements_actifs++;
        }
    }

    return nb_elements_actifs;
}

// Procédure de test pour vérifier la fonction nb_actif
void tester_nb_actif() {
    FILE *fichier = fopen("liste_actifs.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Lire le nombre d'actifs à partir du fichier
    int nb_actifs;
    fscanf(fichier, "nb actifs : %d\n", &nb_actifs);

    // Allouer de la mémoire pour le tableau de pointeurs vers les actifs
    Actif **liste_actifs = (Actif **)malloc(nb_actifs * sizeof(Actif *));

    // Lire les données des actifs à partir du fichier et les stocker dans le tableau
    for (int i = 0; i < nb_actifs; i++) {
        liste_actifs[i] = (Actif *)malloc(sizeof(Actif));
        fscanf(fichier, "%[^,],%[^,],%[^,],%f,%f,%d,%[^\n]\n",
               liste_actifs[i]->ID, liste_actifs[i]->Date, liste_actifs[i]->Description,
               &liste_actifs[i]->MontantNeuf, &liste_actifs[i]->Pourcentage,
               &liste_actifs[i]->Type, liste_actifs[i]->PassifLie);
    }

    // Fermer le fichier après avoir lu les données
    fclose(fichier);

    // Appeler la fonction nb_actif pour obtenir le nombre d'éléments actifs dans la liste
    int nombre_elements_actifs = nb_actif(liste_actifs, nb_actifs);

    // Afficher le résultat
    printf("Nombre d'elements actifs : %d\n", nombre_elements_actifs);

    // Libérer la mémoire allouée pour les actifs
    for (int i = 0; i < nb_actifs; i++) {
        free(liste_actifs[i]);
    }
    free(liste_actifs);
}

// Fonction pour charger les actifs à partir du fichier
Actif* charger_actif(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    // Lecture du nombre d'actifs inscrits dans le fichier
    int nb_actifs;
    fscanf(fichier, "nb actifs : %d\n", &nb_actifs);

    // Création du tableau dynamique pour stocker les actifs
    Actif* liste_actifs = (Actif*)malloc(nb_actifs * sizeof(Actif));

    // Chargement des données depuis le fichier dans le tableau
    for (int i = 0; i < nb_actifs; i++) {
        fscanf(fichier, "%[^,],%[^,],%[^,],%lf,%lf,%d,%[^\n]\n",
               liste_actifs[i].ID,
               liste_actifs[i].Date,
               liste_actifs[i].Description,
               &liste_actifs[i].MontantNeuf,
               &liste_actifs[i].Pourcentage,
               &liste_actifs[i].Type,
               liste_actifs[i].PassifLie
        );
    }

    fclose(fichier);
    return liste_actifs;
}

// Procédure de test
void tester_charger_actif() {
    const char* nom_fichier = "liste_actifs.txt";
    Actif* liste_actifs = charger_actif(nom_fichier);
    if (liste_actifs == NULL) {
        printf("Le chargement des actifs a échoué.\n");
        return;
    }

    // Affichage des actifs chargés pour vérification
    printf("Actifs chargés : \n");
    int nb_actifs = sizeof(liste_actifs) / sizeof(Actif);
    for (int i = 0; i < nb_actifs; i++) {
        printf("ID: %s, Date: %s, Description: %s, MontantNeuf: %.2f, Pourcentage: %.2f, Type: %d, PassifLie: %s\n",
               liste_actifs[i].ID,
               liste_actifs[i].Date,
               liste_actifs[i].Description,
               liste_actifs[i].MontantNeuf,
               liste_actifs[i].Pourcentage,
               liste_actifs[i].Type,
               liste_actifs[i].PassifLie
        );
    }

    // Libération de la mémoire allouée pour la liste des actifs
    free(liste_actifs);
}