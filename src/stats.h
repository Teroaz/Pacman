// STATS.H
// Ce fichier regroupe les prototypes des fonctions présentes dans stats.c

#ifndef PACMAN_STATS_H
#define PACMAN_STATS_H

#include "structures.h"
#include "time.h"
#include "personnage.h"

// fonction qui va appeler toutes les autres fonctions afficher présentes dans le stats.c
void afficher_stats(Partie);

// afficher le niveau et le temps de partie
void afficher_niveauEtDuree(Partie);

// afficher le score de pacman
void afficher_score(Partie);

// afficher les statistiques des bonus mangés / sur le niveau
void afficher_bonus(Partie);

// afficher les points de vie de pacman
void afficher_pointsDeVie(Partie);

// afficher les états de la partie (confusion, freeze et destructo)
void afficher_etats(Partie);

#endif //PACMAN_STATS_H
