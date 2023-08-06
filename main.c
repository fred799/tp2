#include <stdio.h>
#include <stdlib.h>
#include "passifs.h"
#include "actifs.h"
#include "equite.h"

/***************************************
    *** Déclarations des fonctions ***
***************************************/
// Déclaration de la fonction
//void enregistrer_analyser_valeur_nette(struct t_liste_equite* liste, const char* nom_fichier);

// Procédure de test pour la fonction enregistrer_analyser_valeur_nette
//void test_enregistrer_analyser_valeur_nette();



int main(void) {

    int choix_menu = 0;

    charger_passif();

    charger_actif();



    while (choix_menu < 1 || choix_menu > 5) {
        printf("Que voulez-vous faire :\n"
               " 1- Modifier un actifs\n"
               " 2- Modifier un actifs\n"
               " 3- Afficher la valeur nette totale\n "
               "4- Enregistrer les donnees dans un fichier txt\n"
               " 5- Quitter");
        scanf("%i", &choix_menu);


    if (choix_menu == 1) {

        choix_menu = 0;
    }


    else if (choix_menu == 2) {

        choix_menu = 0;
    }


    else if (choix_menu == 3){

        choix_menu = 0;
    }


    else if (choix_menu == 4) {

        choix_menu = 0;
    }


    else if (choix_menu == 5) {

        EXIT_SUCCESS;
    }

    }

}