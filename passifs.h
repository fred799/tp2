#ifndef TP2_PASSIFS_H
#define TP2_PASSIFS_H

typedef struct t_passif passifs;
typedef struct t_liste_passif liste_passifs;

int nb_passif(liste_passif* liste_passifs);
liste_passif* charger_passif(const char* nom_fichier);

void tester_nb_passif();
void tester_charger_passif();

#endif //TP2_PASSIFS_H
