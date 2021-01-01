// FANTOMES.C
// Ce fichier regroupe les fonctions et logiques nécessaires des fantomes du jeu

#include "fantomes.h"

void dessiner_fantomes(Fantome fantome) {
    afficher_image("./images/fantome.bmp", pos2point((Pos) {fantome.pos.l, fantome.pos.c}));
}

void effacer_fantomes(Partie *partie, Fantome fantome) {

    char symbole = partie->plateau[fantome.pos.l][fantome.pos.c];

    // Selon le symbole qui se trouvait à l'emplacement du fantome,
    // on redessine ce qui se trouvait avant
    if (symbole == '.') {
        afficher_image("./images/environnement/bonus.bmp", pos2point(fantome.pos));
    } else if (symbole == 'B') {
        afficher_image("./images/environnement/bonus_puissant.bmp", pos2point(fantome.pos));
    } else {
        dessiner_rectangle(pos2point(fantome.pos), TAILLE_CASE, TAILLE_CASE, noir);
    }
}

void deplacer_fantomes(Partie *partie) {

    // Tableau des fantomes
    Fantome *fantomes = partie->fantomes;

    // Pour chaque fantome
    for (int i = 0; i < 4; i++) {

        // On efface l'ancienne trace du fantome
        effacer_fantomes(partie, fantomes[i]);

        // Attribution de comportements différents selon l'index du fantome dans le tableau des fantomes
        switch (i) {
            case 0:
                // le fantome à l'index 0 va recopier les déplacements de pacman selon le sens inversé de pacman
                recopier_deplacement_pacman(partie, &fantomes[i], 1);
                break;
            case 1:
            case 3:
                // les fantomes à l'index 1 et 3 vont se déplacer selon la distance entre eux et pacman
                deplacement_normal(partie, &fantomes[i]);
                break;
            case 2:
                // le fantome à l'index 2 va recopier les déplacements de pacman selon le sens de pacman
                recopier_deplacement_pacman(partie, &fantomes[i], 0);
                break;

        }

        // si un fantome se situe à la même position que pacman, alors on considère qu'il l'a mangé
        if (fantomes[i].pos.l == partie->pacman.pos.l && fantomes[i].pos.c == partie->pacman.pos.c) {
            if (time(NULL) - partie->pacman.etat.estEnDestructoTime <= DUREE_DESTRUCTO_EN_S) {
                tuer_fantomes_a_la_pos(partie, fantomes[i].pos);
            } else {
                tuer_pacman(partie);
            }
        }

        dessiner_fantomes(fantomes[i]);
    }
}

void debloquer_fantome(Partie *partie, Fantome *fantome) {

    int distance = partie->C * partie->L, autre_distance;
    char sens_choisi;

    // on regarde pour chaque sens (haut, bas, gauche, droite) si la distance entre la position à ce sens est plus courte de celle de pacman,
    // dans ce cas là on ira vers ce sens

    // par défaut on choisit d'aller en haut
    if (!collision_mur(*partie, position_souhaitee(fantome->pos, 'H'))) {
        sens_choisi = 'H';
        distance = manhattan_distance(position_souhaitee(fantome->pos, 'H'), partie->pacman.pos);
    }

    // si on a pas de collision avec un mur
    // on regarde s'il est préférable d'aller à droite en calculant la distance entre la position de la case à droite et de pacman

    if (!collision_mur(*partie, position_souhaitee(fantome->pos, 'D'))) {
        autre_distance = manhattan_distance(position_souhaitee(fantome->pos, 'D'), partie->pacman.pos);
        if (distance > autre_distance) {
            // si la distance avec ce sens est préférable, on choisit ce sens
            sens_choisi = 'D';
            distance = autre_distance;
        }
    }
    if (!collision_mur(*partie, position_souhaitee(fantome->pos, 'B'))) {
        autre_distance = manhattan_distance(position_souhaitee(fantome->pos, 'B'), partie->pacman.pos);
        if (distance > autre_distance) {
            sens_choisi = 'B';
            distance = autre_distance;
        }
    }
    if (!collision_mur(*partie, position_souhaitee(fantome->pos, 'G'))) {
        autre_distance = manhattan_distance(position_souhaitee(fantome->pos, 'G'), partie->pacman.pos);
        if (distance > autre_distance) {
            sens_choisi = 'G';
        }
    }

    // la nouvelle position du fantome est la position préférable, celle qui le rapproche de pacman
    fantome->pos = position_souhaitee(fantome->pos, sens_choisi);
}

void deplacement_normal(Partie *partie, Fantome *fantome) {
    debloquer_fantome(partie, fantome);
}

void recopier_deplacement_pacman(Partie *partie, Fantome *fantome, int inversion_du_sens) {

    // certains fantomes vont recopiant le sens de pacman en inversant ou non son sens, cependant s'il rentre en collision avec un mur
    // on va décider de le déplacer selon la position qui lui permettrait de se rapprocher de pacman sans rester bloqué

    if (!collision_mur(*partie, position_souhaitee(fantome->pos, inversion_du_sens == 1 ? inversion_sens(partie->pacman.sens) : partie->pacman.sens))) {
        fantome->pos = position_souhaitee(fantome->pos, inversion_du_sens == 1 ? inversion_sens(partie->pacman.sens) : partie->pacman.sens);
    } else {
        debloquer_fantome(partie, fantome);
    }
}

int fantome_non_freeze_a_la_position(Partie *partie, Pos pos) {

    for (int f = 0; f < 4; f++) {
        Fantome fantome = partie->fantomes[f];
        if (fantome.pos.l == pos.l && fantome.pos.c == pos.c && !(time(NULL) - fantome.etat.estFreezeTime <= DUREE_FREEZE_EN_S)) {
            return 1;
        }
    }
    return 0;
}

int fantome_freeze_a_la_position(Partie *partie, Pos pos) {

    for (int f = 0; f < 4; f++) {
        Fantome fantome = partie->fantomes[f];
        if (fantome.pos.l == pos.l && fantome.pos.c == pos.c && (time(NULL) - fantome.etat.estFreezeTime <= DUREE_FREEZE_EN_S)) {
            return 1;
        }
    }
    return 0;
}

void tuer_fantomes_a_la_pos(Partie *partie, Pos pos) {

    for (int f = 0; f < 4; f++) {
        Fantome *fantome = &partie->fantomes[f];
        if (fantome->pos.c == pos.c && fantome->pos.l == pos.l) {
            fantome->pos = trouver_position_safe(partie);
            partie->pacman.score += POINTS_FANTOME_MANGE;
        }
    }
}
