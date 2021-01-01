// PERSONNAGE.C
// Ce fichier regroupe les fonctions utilitaires des personnages (pacman & fantomes)

#include "personnage.h"

Pos position_souhaitee(Pos pos, char sens) {

    switch (sens) {
        case 'H':
            pos.l--;
            break;
        case 'D':
            pos.c++;
            break;
        case 'B':
            pos.l++;
            break;
        case 'G':
            pos.c--;
            break;
    }

    return pos;
}

Pos trouver_position_safe(Partie *partie) {
    Pos positions_dispo[partie->L * partie->C];
    int nombreDePosDispos = 0;

    for (int ligne = 0; ligne < partie->L; ligne++) {
        for (int colonne = 0; colonne < partie->C; colonne++) {
            if (collision_mur(*partie, (Pos) {ligne, colonne})) continue;
            for (int i = 0; i < 4; i++) {
                if (abs(partie->fantomes[i].pos.l - ligne) >= 6 && abs(partie->fantomes[i].pos.c - colonne) >= 6) {
                    positions_dispo[nombreDePosDispos] = (Pos) {ligne, colonne};
                    nombreDePosDispos++;
                }
            }
        }
    }

    return positions_dispo[entier_aleatoire(nombreDePosDispos)];
}