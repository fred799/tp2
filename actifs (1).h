#ifndef TP2_ACTIFS_H
#define TP2_ACTIFS_H

typedef struct t_actifs actifs;

typedef struct t_liste_actifs liste_actifs;

int nb_actif(Actif *liste_actifs[], int taille);
Actif* charger_actif(const char* nom_fichier);
char** obtenir_passifs_liés(Actif* liste_actifs, int indice_actif, int* nb_passifs_lies);
float valeur_passifs_lier_actif(Actif *actifs, int indice_actif);

void tester_nb_actif();
void tester_charger_actif();
void test_obtenir_passifs_lies();
void test_valeur_passifs_lier_actif();

#endif //TP2_ACTIFS_H
