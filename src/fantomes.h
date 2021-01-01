// FANTOMES.H
// Ce fichier regroupe les prototypes des fonctions du fichier fantomes.c

#ifndef PACMAN_FANTOMES_H
#define PACMAN_FANTOMES_H

#include "structures.h"
#include "niveau.h"
#include "utils.h"

// dessiner le fantome
void dessiner_fantomes(Fantome);

// effacer le dessin du fantome
void effacer_fantomes(Partie *, Fantome);

// lancer le déplacement de tous les fantomes
void deplacer_fantomes(Partie *);

// déplacer en se basant sur la distance entre pacman et le fantome
void deplacement_normal(Partie *, Fantome *);

void debloquer_fantome(Partie *, Fantome *);

// déplacer en se basant sur le sens de pacman (avec choix de l'inversion du sens ou non)
void recopier_deplacement_pacman(Partie *, Fantome *, int);

// vérifier s'il existe un fantome non gelé par un bonus puissant (gomme) à la position donnée
int fantome_non_freeze_a_la_position(Partie *, Pos);

// vérifier s'il existe un fantome gelé par un bonus puissant (gomme) à la position donnée
int fantome_freeze_a_la_position(Partie *, Pos);

// tuer tous les fantomes présents à une position donnée (les fantomes peuvent se superposer)
void tuer_fantomes_a_la_pos(Partie *, Pos);

#endif
