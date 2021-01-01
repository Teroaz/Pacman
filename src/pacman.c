// PACMAN.C
// Ce fichier regroupe les fonctions et logiques nécessaires pour pacman

#include "pacman.h"

void initialiser_pacman(Pacman *pacman) {
    // pour éviter d'avoir des valeurs inconnues, on initialise les données de la structure de pacman
    pacman->nbrDeVies = NBVIES;
    pacman->sens = 'H';
    pacman->etat.estConfusTime = 0;
    pacman->etat.estEnDestructoTime = 0;
    pacman->bonus.nbrDeBonusNormal = 0;
    pacman->bonus.nbrDeGommes = 0;
    pacman->score = 0;
    pacman->boucheOuverte = 1;
}

void dessiner_pacman(Partie *partie) {

    Pacman *pacman = &partie->pacman;

    // Si pacman est en mode "destructo", on le change complètement
    if ((time(NULL) - pacman->etat.estEnDestructoTime <= DUREE_DESTRUCTO_EN_S)) {
        afficher_image("./images/pacman/destructo.bmp", pos2point(pacman->pos));
    } else {
        // selon le sens vers où se dirige pacman, sa bouche sera ouverte vers celui ci
        if (pacman->boucheOuverte) {
            switch (pacman->sens) {
                case 'H':
                    afficher_image("./images/pacman/pacman_bo_h.bmp", pos2point(pacman->pos));
                    break;
                case 'D':
                    afficher_image("./images/pacman/pacman_bo_d.bmp", pos2point(pacman->pos));
                    break;
                case 'B':
                    afficher_image("./images/pacman/pacman_bo_b.bmp", pos2point(pacman->pos));
                    break;
                case 'G':
                    afficher_image("./images/pacman/pacman_bo_g.bmp", pos2point(pacman->pos));
                    break;
            }
        } else {
            afficher_image("./images/pacman/pacman_bf.bmp", pos2point(pacman->pos));
        }
    }

    // si pacman reste collé à un mur, on évite de lui faire ouvrir / fermer la bouche car il reste statique
    if (!collision_mur(*partie, position_souhaitee(pacman->pos, pacman->sens))) {
        pacman->boucheOuverte = (pacman->boucheOuverte + 1) % 2;
    }

    actualiser();
    // effacer l'ancien dessin de pacman
    dessiner_rectangle(pos2point(pacman->pos), TAILLE_CASE, TAILLE_CASE, noir);

}

// pour chaque déplacement, cette fonction est appelée pour vérifier si à la position de pacman se trouve
// un bonus, ainsi le score sera augmenté et le mode destructo activé
void verification_bonus(Partie *partie) {

    Pacman *pacman = &partie->pacman;

    char symbole = partie->plateau[pacman->pos.l][pacman->pos.c];

    if (symbole == '.' || symbole == 'B') {

        partie->plateau[pacman->pos.l][pacman->pos.c] = ' ';

        if (symbole == '.') {
            pacman->bonus.nbrDeBonusNormal++;
            pacman->score += POINTS_BONUS_NORMAL;
        } else if (symbole == 'B') {
            pacman->bonus.nbrDeGommes++;
            pacman->score += POINTS_BONUS_PUISSANT;
            for (int i = 0; i < 4; i++) {
                partie->fantomes[i].etat.estFreezeTime = time(NULL);
            }

            if (pacman->bonus.nbrDeGommes == partie->bonus.nbrDeGommes) {
                pacman->etat.estEnDestructoTime = time(NULL);
            }
        }
        if (DEBUG == 1) {
            printf("bonus mangé, score désormais à %d\n", partie->pacman.score);
        }
    }
}


void deplacer_pacman(Partie *partie, int automatique) {

    int *touches = partie->events->touches;
    Pacman *pacman = &partie->pacman;

    char sens;

    // Si on appelle la fonction sans vouloir que le déplacement est automatique
    if (!automatique) {
        // On récupère le sens voulu par le joueur
        char sens_voulu = touche2sens(recuperer_touche_appuyee(touches));

        // ternaire : si pacman est confus, on inverse le sens voulu, sinon son sens sera le sens voulu
        sens = (time(NULL) - pacman->etat.estConfusTime <= DUREE_CONFUSION_EN_S) ? inversion_sens(sens_voulu)
                                                                                 : sens_voulu;

        // si la touche appuyée n'est pas une des touches de déplacement ou aucune touche, on passe en mode automatique
        if (sens != 'H' && sens != 'B' && sens != 'D' && sens != 'G') {
            return deplacer_pacman(partie, 1);
        }
    } else {
        sens = partie->pacman.sens;
    }

    Pos pos_souhaitee_avec_sens_choisi = position_souhaitee(pacman->pos, sens);
    Pos pos_souhaitee_ancien_sens_valide = position_souhaitee(pacman->pos, pacman->sens);

    // Si pacman ne touche pas de bordure à la position souhaitée
    if (!touche_bordure(*partie, pos_souhaitee_avec_sens_choisi)) {

        // S'il ne rentre pas en collision avec un mur
        if (!collision_mur(*partie, pos_souhaitee_avec_sens_choisi)) {
            // Nous vérifions quand même s'il veut aller sur la case d'un fantome
            if (fantome_freeze_a_la_position(partie, pos_souhaitee_avec_sens_choisi)) {
                // si les fantomes sont freeze, on les tue
                tuer_fantomes_a_la_pos(partie, pos_souhaitee_avec_sens_choisi);
            } else if (fantome_non_freeze_a_la_position(partie, pos_souhaitee_avec_sens_choisi)) {
                // si on va sur un fantome non freeze, on tue pacman
                tuer_pacman(partie);
            } else {
                // S'il n'y a pas de fantomes, nous le déplaçons
                pacman->pos = pos_souhaitee_avec_sens_choisi;
                if (pacman->sens != sens) {
                    pacman->sens = sens;
                }
            }
        } else if (!collision_mur(*partie, pos_souhaitee_ancien_sens_valide)) {
            // Si nous spammons une touche de déplacement qui nous fait rentrer en collision avec un mur, nous pouvions
            // sans cette condition là, rester statique (correction d'use bug)
            pacman->pos = pos_souhaitee_ancien_sens_valide;
        } else {
            // mode destructo
            if ((time(NULL) - pacman->etat.estEnDestructoTime <= DUREE_DESTRUCTO_EN_S)) {
                if (collision_mur(*partie, pos_souhaitee_ancien_sens_valide) == 1) {
                    // destruction du mur sur le plateau
                    partie->plateau[pos_souhaitee_ancien_sens_valide.l][pos_souhaitee_ancien_sens_valide.c] = ' ';
                    dessiner_rectangle(pos2point(pos_souhaitee_ancien_sens_valide), TAILLE_CASE, TAILLE_CASE, noir);
                    if (position_est_un_contour(*partie, pos_souhaitee_ancien_sens_valide)) {
                        // si un contour a été détruit, on actualise la liste des tunnels
                        recuperer_liste_tunnels(partie);
                    }
                }
            }
        }

    } else {
        passage_tunnel(partie, &pacman->pos);
        pacman->etat.estConfusTime = time(NULL);
    }

    verification_bonus(partie);

    dessiner_pacman(partie);
}

void tuer_pacman(Partie *partie) {
    Pacman *pacman = &partie->pacman;

    if ((time(NULL) - pacman->etat.estEnDestructoTime <= DUREE_DESTRUCTO_EN_S)) return;

    pacman->nbrDeVies--;
    if (pacman->nbrDeVies > 0) {
        pacman->score += POINTS_MORT_PACMAN;
        // on téléporte pacman à un endroit "sécurisé"
        pacman->pos = trouver_position_safe(partie);
    }
}

int a_mange_tous_les_bonus(Partie partie) {
    return partie.pacman.bonus.nbrDeBonusNormal == partie.bonus.nbrDeBonusNormal &&
           partie.pacman.bonus.nbrDeGommes == partie.bonus.nbrDeGommes;
}


void passage_tunnel(Partie *partie, Pos *pos) {

    // Liste des tunnels
    Tunnel *tunnels = &partie->tunnels;

    //On tire au hasard un tunnel parmi les tunnels du niveau
    Pos position_nouveau_tunnel = tunnels->tunnel[entier_aleatoire(tunnels->nbrDeTunnels)];

    // Si le tunnel tiré est le tunnel où se positionne un personnage, on refait un tirage aléatoire du tunnel
    // Et ceci de manière récursive tant que le tunnel choisi n'est pas un tunnel où se situe pas le personnage
    if (position_nouveau_tunnel.c == pos->c && position_nouveau_tunnel.l == pos->l) {
        return passage_tunnel(partie, pos);
    } else {
        // On téléporte le personnage à la position du tunnel
        pos->c = position_nouveau_tunnel.c;
        pos->l = position_nouveau_tunnel.l;
    }

}