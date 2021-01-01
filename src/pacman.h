// PACMAN.H
// Ce fichier regroupe les prototypes des fonctions pacman.c, des defines définissant le nombre de points gagnés
// par bonus, par fantome mangé ou par point de vie perdu mais également le nombre de points de vie
// avec comme d'habitude les importations d'autres fichiers .h

#ifndef PACMAN_PACMAN_H
#define PACMAN_PACMAN_H

#include "structures.h"
#include "niveau.h"
#include "utils.h"
#include "time.h"
#include "personnage.h"

#define NBVIES 3

// Points gagnés par les différents bonus ou évènements (fantome mangé / vie perdue)
#define POINTS_BONUS_NORMAL 1
#define POINTS_BONUS_PUISSANT 20
#define POINTS_FANTOME_MANGE 10
#define POINTS_MORT_PACMAN -20

// Définir les valeurs par défaut de pacman au lancement du niveau
void initialiser_pacman(Pacman *);

// Supprime l'ancien dessin de pacman et le re-dessine en prenant compte de si la bouche est ouverte ou non
void dessiner_pacman(Partie *);

// vérifie si pacman mange un bonus
void verification_bonus(Partie *);

void deplacer_pacman(Partie *, int);

void tuer_pacman(Partie *partie);

// vérifie si pacman a mangé tous les bonus (normaux + gommes), retourne 1 si c'est le cas, sinon 0
int a_mange_tous_les_bonus(Partie);

// téléporte pacman à un autre tunnel en prenant compte des tunnels disponibles dans le niveau
void passage_tunnel(Partie *, Pos *);


#endif //PACMAN_PACMAN_H
