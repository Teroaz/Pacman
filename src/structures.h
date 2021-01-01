// STATS.H
// Ce fichier regroupe toutes les structures utilisées dans le projet

#ifndef PACMAN_STRUCTURES_H
#define PACMAN_STRUCTURES_H

#include "../lib/libgraphique.h"

// STRUCTURES
/* Structure Pos: permet de stocker un couple ligne/colonne                   */
typedef struct pos {
    int l;
    int c;
} Pos;

// Structure etat : contient les timestamps permettant de savoir si un effet est actif ou non
typedef struct etat {
    long estConfusTime; // timestamp de la dernière confusion
    long estEnDestructoTime; // timestamp de la dernière fois en mode destructo
    long estFreezeTime; // timestamp de la dernière fois que les fantomes ont été gelés
} Etat;

// Structure fantome : contient la position et l'état du fantome
typedef struct fantome {
    Pos pos; // position du fantome
    Etat etat; // état du fantome (seulement utile pour le freeze)
} Fantome;

// Structure bonus : contient le nombre de bonus normal et le nombre de bonus puissant (gomme)
// est utilisé dans la structure partie pour définir le nombre total de bonus
// et dans la structure pacman pour déterminer le nombre de bonus mangés
typedef struct bonus {
    int nbrDeBonusNormal;
    int nbrDeGommes;
} Bonus;

// Structure de pacman, le joueur
typedef struct pacman {
    Pos pos; // Position de pacman
    char sens; // sens vers où s'oriente pacman

    int nbrDeVies;  // Nombre de vies restantes
    Bonus bonus; // bonus normaux & puissants mangés
    int score; // Score du joueur
    Etat etat; // Etats de pacman (utilisé pour destructo & confusion)
    int boucheOuverte; // permet de définir si la bouche de pacman est ouverte ou non (servant de booléen)
} Pacman;

typedef struct tunnel {
    int nbrDeTunnels; // nombre de tunnels présents dans le niveau
    Pos tunnel[100]; // tableau des position des tunnels disponibles
} Tunnel;

/* Structure Partie:  permet de stocker les paramètres d'une partie           */
typedef struct partie {
    int niveau; // niveau de la partie
    long timestamp; // time(NULL) au lancement du niveau, utilisé pour récupérer la durée de la partie
    char **plateau; // le tableau de caractères contenant le plateau de jeu
    int L; // le nb de lignes du plateau de jeu
    int C; // le nb de colonne du plateau de jeu
    Pacman pacman; // pacman
    Fantome fantomes[4]; // les fantomes
    Bonus bonus; // bonus normal & puissant (gomme) à manger
    Trace_evts *events; // Evenements des touches pressées
    Tunnel tunnels; // Positions des tunnels de la partie
} Partie;


#endif //PACMAN_STRUCTURES_H
