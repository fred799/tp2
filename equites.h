#ifndef TP2_EQUITES_H
#define TP2_EQUITES_H

typedef struct t_equite equite;

typedef struct t_liste_equite liste_equite;

liste_equite* analyse_valeur_nette_totale(equite* actifs, int nbr_actifs, equite* passifs, int nbr_passifs);


#endif //TP2_EQUITES_H
