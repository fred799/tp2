#include "actifs.h"

// Définition de la structure t_passif
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

// Définition de la structure t_liste_passif
struct t_liste_actifs{
    actifs* tableau;
    int nombre_cases;
} ;

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

char** obtenir_passifs_liés(Actif* liste_actifs, int indice_actif, int* nb_passifs_lies) {
    // Vérifier si l'indice_actif est valide
    if (indice_actif < 0 || indice_actif >= *nb_actifs) {
        fprintf(stderr, "Indice d'actif invalide.\n");
        *nb_passifs_lies = 0;
        return NULL;
    }

    // Récupérer l'actif ciblé par l'indice
    Actif actif_cible = liste_actifs[indice_actif];

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

void test_obtenir_passifs_lies() {
    int nb_actifs, nb_passifs;
    Actif* liste_actifs = charger_actif("liste_actifs.txt", &nb_actifs);
    char** liste_passifs = charger_passif("liste_passifs.txt", &nb_passifs);

    // Exemple d'utilisation de la fonction obtenir_passifs_liés pour le premier actif (indice 0)
    int nb_passifs_lies;
    char** passifs_lies = obtenir_passifs_liés(liste_actifs, 0, &nb_passifs_lies);

    // Afficher les passifs liés à l'actif ciblé
    printf("Nombre de passifs liés : %d\n", nb_passifs_lies);
    for (int i = 0; i < nb_passifs_lies; i++) {
        printf("Passif lié %d : %s\n", i + 1, passifs_lies[i]);
    }

    // Libérer la mémoire allouée pour les passifs liés
    for (int i = 0; i < nb_passifs_lies; i++) {
        free(passifs_lies[i]);
    }
    free(passifs_lies);

    // Libérer la mémoire allouée pour les actifs et les passifs
    for (int i = 0; i < nb_actifs; i++) {
        for (int j = 0; j < liste_actifs[i].nbPassifsLies; j++) {
            free(liste_actifs[i].PassifsLies[j]);
        }
        free(liste_actifs[i].PassifsLies);
    }
    free(liste_actifs);

    for (int i = 0; i < nb_passifs; i++) {
        free(liste_passifs[i]);
    }
    free(liste_passifs);
}

// Fonction qui calcule la somme des dettes passives reliées à un actif
float valeur_passifs_lier_actif(Actif *actifs, int indice_actif) {
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

// Procédure de test
void test_valeur_passifs_lier_actif() {
    // Création des passifs
    Passif passif1 = { "Passif 1", 100.0 };
    Passif passif2 = { "Passif 2", 200.0 };
    Passif passif3 = { "Passif 1", 50.0 };  // Même description que passif1
    Passif passif4 = { "Passif 3", 300.0 };

    // Création des actifs et leurs passifs respectifs
    Passif passifs_actif1[] = { passif1, passif2 };
    Actif actif1 = { "Actif 1", passifs_actif1, 2 };

    Passif passifs_actif2[] = { passif3, passif4 };
    Actif actif2 = { "Actif 2", passifs_actif2, 2 };

    Actif actifs[] = { actif1, actif2 };

    // Test de la fonction avec l'actif1 (doit retourner 300.0)
    float somme_passifs_actif1 = valeur_passifs_lier_actif(actifs, 0);
    printf("Somme des passifs reliés à l'actif 1 : %.2f\n", somme_passifs_actif1);

    // Test de la fonction avec l'actif2 (doit retourner 350.0)
    float somme_passifs_actif2 = valeur_passifs_lier_actif(actifs, 1);
    printf("Somme des passifs reliés à l'actif 2 : %.2f\n", somme_passifs_actif2);
}

// Fonction pour modifier la valeur d'un passif dans la liste d'actifs
void modifier_solde_actif(liste_actifs* liste, int indice_passif, double nouvelle_valeur) {
    if (liste == NULL || indice_passif < 0 || indice_passif >= liste->nombre_cases) {
        printf("Erreur : indice_passif invalide ou liste NULL.\n");
        return;
    }

    // Modification de la valeur du passif ciblé par l'indice reçu en paramètre
    liste->tableau[indice_passif].valeur_init = nouvelle_valeur;
}

// Procédure de test pour la fonction modifier_solde_actif
void tester_modifier_solde_actif() {
    // Création d'une liste d'actifs de test
    actifs actif1 = { "A001", 2023, "Description actif 1", 1000.0, 50.0, 1, 2 };
    char* passifs_actif1[] = { "Passif1", "Passif2" };
    actif1.passifs_lies = passifs_actif1;

    actifs actif2 = { "A002", 2023, "Description actif 2", 2000.0, 30.0, 2, 1 };
    char* passifs_actif2[] = { "Passif3" };
    actif2.passifs_lies = passifs_actif2;

    actifs actif3 = { "A003", 2023, "Description actif 3", 3000.0, 20.0, 3, 0 };
    actif3.passifs_lies = NULL;

    actifs liste_actifs[] = { actif1, actif2, actif3 };
    liste_actifs liste = { liste_actifs, 3 };

    // Affichage des actifs avant modification
    printf("Avant modification :\n");
    for (int i = 0; i < liste.nombre_cases; i++) {
        printf("Actif %d - Description : %s, Valeur initiale : %.2lf\n", i+1, liste.tableau[i].description, liste.tableau[i].valeur_init);
    }

    // Test de modification du solde du premier actif
    modifier_solde_actif(&liste, 0, 1500.0);

    // Affichage des actifs après modification
    printf("\nAprès modification :\n");
    for (int i = 0; i < liste.nombre_cases; i++) {
        printf("Actif %d - Description : %s, Valeur initiale : %.2lf\n", i+1, liste.tableau[i].description, liste.tableau[i].valeur_init);
    }
}

void test_module_actif()
{
    
}

void test_module_actif_p2()
{
    
}
