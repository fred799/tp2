#include "equites.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct t_equite {
    char cle_unique[6];
    char description[50];
    double val_net;
};

struct liste_equite {
    equite* tableau;
    int nbr_case;
};

