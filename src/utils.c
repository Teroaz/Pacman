// UTILS.C
// Ce fichier regroupe des fonctions utilitaires utilisées partout dans le projet

#include "utils.h"
#include "niveau.h"

Point pos2point(Pos pos) {

    // retourne de manière proportionnelle les coordonnées du point graphique à l'aide
    // de la position dans la plateau
    return (Point) {pos.c * TAILLE_CASE, pos.l * TAILLE_CASE};
}

char inversion_sens(char sens) {

    switch (sens) {
        case 'H':
            return 'B';
        case 'D':
            return 'G';
        case 'B':
            return 'H';
        case 'G':
            return 'D';
    }

    // pour éviter d'avoir un warning, N = null
    return 'N';
}

char touche2sens(int touche) {

    switch (touche) {
        case SDLK_z:
            return 'H';
        case SDLK_d:
            return 'D';
        case SDLK_s:
            return 'B';
        case SDLK_q:
            return 'G';
    }

    // pour éviter d'avoir un warning, on va considérer que N = null
    return 'N';
}

int recuperer_touche_appuyee(int *touches) {

    // Parmi toutes les touches appuyées, si un index correspondant à un code de touche est égal à 1, c'est que
    // cette touche est appuyée, on la retourne donc directement après qu'elle ait été trouvée.
    for (int i = 0; i < 323; i++) {
        if (touches[i] == 1) {
            return i;
        }
    }

    // le cas échéant (aucune touche appuyée)
    return -1;
}

int manhattan_distance(Pos premierePos, Pos deuxiemePos) {

    // distance entre 2 points en utilisant la formule de manhattan
    return abs(deuxiemePos.l - premierePos.l) + abs(deuxiemePos.c - premierePos.c);
}

int collision_mur(Partie partie, Pos pos) {

    if (touche_bordure(partie, pos)) return 2;
    return partie.plateau[pos.l][pos.c] == '*';
}

int touche_bordure(Partie partie, Pos pos) {

    // si une des comparaisons est vraie, la fonction retourne 1, sinon si elles sont toutes fausses, la fonction
    // retourne 0
    return pos.l < 0 || pos.c < 0 || pos.l >= partie.L || pos.c >= partie.C;
}


int position_est_un_contour(Partie partie, Pos pos) {
    // si une position appartient au contour du plateau, retourne 1, sinon 0
    return (pos.l == 0 || pos.l == partie.L - 1) || (pos.c == 0 || pos.c == partie.C - 1);
}