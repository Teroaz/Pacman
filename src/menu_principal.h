// MENU_PRINCIPAL.H
// Ce fichier regroupe les prototypes des fonctions, quelques defines contenant les dimensiosn de la fenêtre
// et un autre pour définir le nombre de niveaux (maps)

#ifndef PACMAN_MENU_PRINCIPAL_H
#define PACMAN_MENU_PRINCIPAL_H

#include "../lib/libgraphique.h"
#include "niveau.h"

#define MAXH 800
#define MAXV 600

#define NBR_DE_MAPS 3

void lancer_jeu(int);

void ecran_daccueil();

void passage_niveau_superieur(int);

void fin_partie(int, int);


#endif //PACMAN_MENU_PRINCIPAL_H
