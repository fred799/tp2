#ifndef TP2_ACTIFS_H
#define TP2_ACTIFS_H

typedef struct t_actifs actifs;

typedef struct t_liste_actifs liste_actifs;

int nb_actif(Actif *liste_actifs[], int taille);
Actif* charger_actif(const char* nom_fichier);

void tester_nb_actif();
void tester_charger_actif();

#endif //TP2_ACTIFS_H
