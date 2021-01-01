// NIVEAU.H
// Ce fichier regroupe les prototypes des fonctions présentes dans niveau.c et les importations des autres fichiers .h
// nécessaires

#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include "structures.h"
#include "pacman.h"
#include "main.h"
#include "utils.h"
#include "fantomes.h"
#include "../lib/libgraphique.h"
#include "stats.h"

// PROTOTYPES
/* charge_plan : lit un fichier contenant un plateau de jeu et le charge
                    en mémoire, dans le champ 'plateau' d'une Partie */
Partie charge_plan(char *fichier);

// démarre le déroulement des données d'une partie reçue par la fonction charge_plan
void charge_partie(Partie *);

// dessine l'environnement (mur et bonus) de la partie
void dessiner_plateau(Partie);

// récupérer les tunnels de la partie actuelle
void recuperer_liste_tunnels(Partie *);

#endif
