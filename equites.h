#ifndef TP2_EQUITES_H
#define TP2_EQUITES_H

typedef struct t_equite equite;

typedef struct t_liste_equite liste_equite;

liste_equite* analyse_valeur_nette_totale(equite* actifs, int nbr_actifs, equite* passifs, int nbr_passifs);

// Déclaration de la fonction
void enregistrer_analyser_valeur_nette(struct t_liste_equite* liste, const char* nom_fichier);

// Procédure de test pour la fonction enregistrer_analyser_valeur_nette
void test_enregistrer_analyser_valeur_nette();

#endif //TP2_EQUITES_H
