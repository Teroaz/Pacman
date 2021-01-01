// UTILS.H
// Ce fichier regroupe les prototypes des fonctions utilitaires présentes dans utils.c

#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

#include "structures.h"

#define CARRE(a) ((a) * (a))

// convertir une position (plateua) en point (graphique)
Point pos2point(Pos);

// Récupérer le sens souhaité par rapport au code d'une des 4 touches de déplacement
char touche2sens(int);

// inverse le caractère indiquant le sens vers où souhaite se diriger un personnage
char inversion_sens(char);

// récupérer la touche appuyée
int recuperer_touche_appuyee(int *);

// calculer la distance "manhattan" entre 2 positions
int manhattan_distance(Pos, Pos);

// Retourne 1 si à la position donnée sur le plateau se trouve un mur ou que nous touchons une bordure
// Sinon retourne 0 si la voie est "libre"
int collision_mur(Partie, Pos);

// Retourne 1 si la position donnée a une des coordonnées négatives ou qu'elle est en dehors du plateau
int touche_bordure(Partie, Pos);

// Vérifier si une position appartient au contour du plateau
int position_est_un_contour(Partie, Pos);

#endif //PACMAN_UTILS_H
