#include "passifs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct t_passifs{
    char id[6];
    char description[51];
    double solde;
} ;


struct t_liste_passifs{
    passifs* tableau;
    int nombre_cases;
} ;


char* obtenir_id_passif(liste_passifs* liste, int indice_ele_id){

    if (liste == NULL || indice_ele_id < 0 || indice_ele_id >= liste->nombre_cases){
        return 0;
    }

    return liste->tableau[indice_ele_id].id;

}

// printf("Test no 3 - obtenir_id_passif()\n \t Valeur attendue: %s \n \t Valeur obtenue: p3 \n", obtenir_id_passif(liste, 8));



char* obtenir_description_passif(liste_passifs* liste, int indice_ele_desc){

    if (liste == NULL || indice_ele_desc < 0 || indice_ele_desc >= liste->nombre_cases){
        return 0;
    }

    return liste->tableau[indice_ele_desc].description;

}

double obtenir_solde_passif(liste_passifs* liste, int indice_ele_solde){

    if (liste == NULL || indice_ele_solde < 0 || indice_ele_solde >= liste->nombre_cases){
        return 0;
    }

    return liste->tableau[indice_ele_solde].solde;

}


