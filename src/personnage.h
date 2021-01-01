// PERSONNAGE.H
// Ce fichier regroupe les prototypes des fonctions présentes dans personnage.c ainsi que les durées en seconde des
// différents effets du jeu

#ifndef PACMAN_PERSONNAGE_H
#define PACMAN_PERSONNAGE_H

#include "../lib/libgraphique.h"
#include "structures.h"
#include "utils.h"

// durée des différents effets
#define DUREE_FREEZE_EN_S 5
#define DUREE_CONFUSION_EN_S 5
#define DUREE_DESTRUCTO_EN_S 15

// retourne la position souhaitée selon le sens d'un personnage
Pos position_souhaitee(Pos, char);

// retourne une position sécurisée pour éviter de tuer dès la réapparition
Pos trouver_position_safe(Partie *);

#endif //PACMAN_PERSONNAGE_H
