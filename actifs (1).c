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
int nb_actif(t_liste_actifs liste) {
    int nb_elements_actifs = 0;

    for (int i = 0; i < liste.nombre_cases; i++) {
        if (liste.tableau[i].id[0] != '\0') {
            nb_elements_actifs++;
        }
    }

    return nb_elements_actifs;
}

// Procédure de test pour vérifier la fonction nb_actif
void tester_nb_actif() {
    FILE* fichier = fopen("liste_actifs.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Lire le nombre d'actifs à partir du fichier
    int nb_actifs;
    fscanf(fichier, "nb actifs : %d\n", &nb_actifs);

    // Allouer de la mémoire pour le tableau de structures d'actifs
    t_liste_actifs liste_actifs;
    liste_actifs.tableau = (actifs*)malloc(nb_actifs * sizeof(actifs));

    // Lire les données des actifs à partir du fichier et les stocker dans le tableau
    for (int i = 0; i < nb_actifs; i++) {
        fscanf(fichier, "%[^,],%d,%[^,],%lf,%lf,%d,%d",
               liste_actifs.tableau[i].id, &liste_actifs.tableau[i].annee,
               liste_actifs.tableau[i].description, &liste_actifs.tableau[i].valeur_init,
               &liste_actifs.tableau[i].pourcentage, &liste_actifs.tableau[i].type,
               &liste_actifs.tableau[i].nbr_passifs);

        if (liste_actifs.tableau[i].nbr_passifs > 0) {
            liste_actifs.tableau[i].passifs_lies = (char**)malloc(liste_actifs.tableau[i].nbr_passifs * sizeof(char*));
            for (int j = 0; j < liste_actifs.tableau[i].nbr_passifs; j++) {
                liste_actifs.tableau[i].passifs_lies[j] = (char*)malloc(3 * sizeof(char));
                fscanf(fichier, ",%[^,\n]", liste_actifs.tableau[i].passifs_lies[j]);
            }
        }
    }

    // Fermer le fichier après avoir lu les données
    fclose(fichier);

    // Initialiser le nombre de cases dans la structure de liste_actifs
    liste_actifs.nombre_cases = nb_actifs;

    // Appeler la fonction nb_actif pour obtenir le nombre d'éléments actifs dans la liste
    int nombre_elements_actifs = nb_actif(liste_actifs);

    // Afficher le résultat
    printf("Nombre d'elements actifs : %d\n", nombre_elements_actifs);

    // Libérer la mémoire allouée pour les passifs
    for (int i = 0; i < liste_actifs.nombre_cases; i++) {
        for (int j = 0; j < liste_actifs.tableau[i].nbr_passifs; j++) {
            free(liste_actifs.tableau[i].passifs_lies[j]);
        }
        if (liste_actifs.tableau[i].nbr_passifs > 0) {
            free(liste_actifs.tableau[i].passifs_lies);
        }
    }

    // Libérer la mémoire allouée pour les actifs
    free(liste_actifs.tableau);
}

// Fonction pour charger les actifs à partir du fichier
t_liste_actifs charger_actif(const char* nom_fichier) {
    struct t_liste_actifs liste_actifs;

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        liste_actifs.tableau = NULL;
        liste_actifs.nombre_cases = 0;
        return liste_actifs;
    }

    // Lecture du nombre d'actifs inscrits dans le fichier
    int nb_actifs;
    fscanf(fichier, "nb actifs : %d\n", &nb_actifs);

    // Allocation de mémoire pour le tableau d'actifs
    liste_actifs.tableau = (actifs*)malloc(nb_actifs * sizeof(actifs));
    liste_actifs.nombre_cases = nb_actifs;

    // Chargement des données depuis le fichier dans le tableau
    for (int i = 0; i < nb_actifs; i++) {
        actifs* actif = &liste_actifs.tableau[i];
        fscanf(fichier, "%5[^,],%d,%50[^,],%lf,%lf,%d,%d",
               actif->id,
               &actif->annee,
               actif->description,
               &actif->valeur_init,
               &actif->pourcentage,
               &actif->type,
               &actif->nbr_passifs
        );

        // Allocation de mémoire pour les passifs liés
        actif->passifs_lies = (char**)malloc(actif->nbr_passifs * sizeof(char*));

        // Lecture des passifs liés
        for (int j = 0; j < actif->nbr_passifs; j++) {
            actif->passifs_lies[j] = (char*)malloc(3 * sizeof(char));
            fscanf(fichier, ",%2[^,\n]", actif->passifs_lies[j]);
        }
        fscanf(fichier, "\n"); // Lire le saut de ligne restant
    }

    fclose(fichier);
    return liste_actifs;
}

// Procédure de libération de mémoire
void liberer_liste_actifs(struct t_liste_actifs* liste) {
    for (int i = 0; i < liste->nombre_cases; i++) {
        struct t_actifs* actif = &liste->tableau[i];
        for (int j = 0; j < actif->nbr_passifs; j++) {
            free(actif->passifs_lies[j]);
        }
        free(actif->passifs_lies);
    }
    free(liste->tableau);
}

// Procédure de test
void tester_charger_actif() {
    const char* nom_fichier = "liste_actifs.txt";
    struct t_liste_actifs liste_actifs = charger_actif(nom_fichier);
    if (liste_actifs.tableau == NULL) {
        printf("Le chargement des actifs a échoué.\n");
        return;
    }

    // Affichage des actifs chargés pour vérification
    printf("Actifs chargés : \n");
    for (int i = 0; i < liste_actifs.nombre_cases; i++) {
        struct t_actifs* actif = &liste_actifs.tableau[i];
        printf("ID: %s, Année: %d, Description: %s, ValeurInit: %.2f, Pourcentage: %.2f, Type: %d, NbrPassifs: %d, PassifsLiés: ",
               actif->id,
               actif->annee,
               actif->description,
               actif->valeur_init,
               actif->pourcentage,
               actif->type,
               actif->nbr_passifs
        );
        for (int j = 0; j < actif->nbr_passifs; j++) {
            printf("%s ", actif->passifs_lies[j]);
        }
        printf("\n");
    }

    // Libération de la mémoire allouée
    liberer_liste_actifs(&liste_actifs);
}

char** obtenir_passifs_lies(actifs* liste_actifs, int indice_actif, int* nb_passifs_lies) {
    // Vérifier si l'indice_actif est valide
    if (indice_actif < 0 || indice_actif >= liste_actifs->nombre_cases) {
        fprintf(stderr, "Indice d'actif invalide.\n");
        *nb_passifs_lies = 0;
        return NULL;
    }

    // Récupérer l'actif ciblé par l'indice
    actifs* actif_cible = liste_actifs->tableau[indice_actif];

    // Compter le nombre de passifs liés
    int nb_passifs = 0;
    for (int i = 0; i < actif_cible.nbr_passifs; i++) {
        if (actif_cible.passifs_lies[i] != NULL) {
            nb_passifs++;
        }
    }

    // Allouer de la mémoire pour le tableau des ID des passifs liés
    char** passifs_lies = (char**)malloc(nb_passifs * sizeof(char*));

    // Remplir le tableau avec les ID des passifs liés
    int index = 0;
    for (int i = 0; i < actif_cible.nbr_passifs; i++) {
        if (actif_cible.passifs_lies[i] != NULL) {
            passifs_lies[index] = strdup(actif_cible.passifs_lies[i]);
            index++;
        }
    }

    // Écrire le nombre de passifs liés dans la référence passée en paramètre
    *nb_passifs_lies = nb_passifs;

    return passifs_lies;
}

void test_obtenir_passifs_lies() {
    // Charger les données d'actifs et passifs depuis les fichiers
    t_liste_actifs* liste_actifs = charger_actif("liste_actifs.txt");
    int nb_passifs;
    char** liste_passifs = charger_passif("liste_passifs.txt", &nb_passifs);

    // Exemple d'utilisation de la fonction obtenir_passifs_lies pour le premier actif (indice 0)
    int nb_passifs_lies;
    char** passifs_lies = obtenir_passifs_lies(liste_actifs.tableau, 0, &nb_passifs_lies);

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
    for (int i = 0; i < liste_actifs.nombre_cases; i++) {
        for (int j = 0; j < liste_actifs.tableau[i].nbr_passifs; j++) {
            free(liste_actifs.tableau[i].passifs_lies[j]);
        }
        free(liste_actifs.tableau[i].passifs_lies);
    }
    free(liste_actifs.tableau);

    for (int i = 0; i < nb_passifs; i++) {
        free(liste_passifs[i]);
    }
    free(liste_passifs);
}

// Fonction qui calcule la somme des dettes passives reliées à un actif
double valeur_passifs_lier_actif(t_liste_actifs* liste_actifs, int indice_actif, t_liste_passifs* liste_passifs) {
    double somme_passifs = 0.0;

    // Vérification des paramètres
    if (liste_actifs == NULL || liste_passifs == NULL || indice_actif < 0 || indice_actif >= liste_actifs->nombre_cases) {
        printf("Erreur: Paramètres invalides.\n");
        return somme_passifs;
    }

    // Récupération de l'actif à analyser
    t_actifs actif_analyser = liste_actifs->tableau[indice_actif];

    // Parcours des passifs reliés à l'actif
    for (int i = 0; i < actif_analyser.nbr_passifs; i++) {
        // Recherche du passif dans la liste de passifs
        for (int j = 0; j < liste_passifs->nombre_passifs; j++) {
            if (strcmp(actif_analyser.passifs_lies[i], liste_passifs->passifs[j].id) == 0) {
                somme_passifs += liste_passifs->passifs[j].solde;
                break;
            }
        }
    }

    return somme_passifs;
}

// Procédure de test
void test_valeur_passifs_lier_actif() {
    // Création des passifs
    t_passifs* passif1 = { "P1", "Carte credit Mastercard", 29.30 };
    t_passifs* passif2 = { "P2", "Carte credit Visa", 1441.31 };

    // Création de la liste de passifs
    t_passifs* passifs[] = { passif1, passif2 };
    t_liste_passifs* liste_passifs = { passifs, 2 };

    // Création des actifs
    char* passifs_lies_actif1[] = { "P1" };
    t_actifs actif1 = { "A1", 2023, "Compte Cheque", 1000.0, 0.1, 1, 1, passifs_lies_actif1 };

    char* passifs_lies_actif2[] = { "P2" };
    t_actifs actif2 = { "A2", 2023, "REER", 1500.0, 0.2, 2, 1, passifs_lies_actif2 };

    t_actifs actifs[] = { actif1, actif2 };
    t_liste_actifs liste_actifs = { actifs, 2 };

    // Test de la fonction avec l'actif1 (doit retourner 100.0)
    double somme_passifs_actif1 = valeur_passifs_lier_actif(&liste_actifs, 0, &liste_passifs);
    printf("Somme des passifs reliés à l'actif 1 : %.2f\n", somme_passifs_actif1);

    // Test de la fonction avec l'actif2 (doit retourner 200.0)
    double somme_passifs_actif2 = valeur_passifs_lier_actif(&liste_actifs, 1, &liste_passifs);
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
// Donction pour trouver l'indice de l'actif avec l'id donné dans la liste
int trouver_indice_actif(const t_liste_actif* liste, const char* id_actif) {
    for (int i = 0; i < liste->nombreActifs; i++) {
        if (strcmp(liste->tableau[i].id, id_actif) == 0) {
            return i; // Indice trouvé
        }
    }
    return -1; // Indice non trouvé (valeur -1 indique l'absence de l'actif dans la liste)
}

// Fonction pour libérer la mémoire occupée par la liste d'actifs
void detruire_liste_actif(t_liste_actif* liste) {
    for (int i = 0; i < liste->nombreActifs; i++) {
        for (int j = 0; j < liste->tableau[i].nombrePassifs; j++) {
            free(liste->tableau[i].passifsRelies[j]);
        }
        free(liste->tableau[i].passifsRelies);
    }
    free(liste->tableau);
    liste->tableau = NULL;
    liste->nombreActifs = 0;
    free(liste);
}
 
