// STATS.C
// Ce fichier regroupe les fonctions affichant les statistiques en jeu présentes dans le panneau à droite de la
// fenêtre graphique

#include "stats.h"

void afficher_stats(Partie partie) {

    afficher_image("./images/panneau/scoreboard.bmp", (Point) {462, 0});

    afficher_niveauEtDuree(partie);
    afficher_score(partie);
    afficher_bonus(partie);
    afficher_pointsDeVie(partie);
    afficher_etats(partie);
}

void afficher_niveauEtDuree(Partie partie) {
    // niveau
    char niveau[9];
    sprintf(niveau, "NIVEAU %d", partie.niveau);
    afficher_texte(niveau, 22, (Point) {479, 120}, perso_bleuclair);

    // duree
    char duree[9];
    long secondes = time(NULL) - partie.timestamp;
    sprintf(duree, "%02ld:%02ld:%02ld", secondes / 3600, (secondes / 60) % 60, secondes % 60);
    afficher_texte(duree, 14, (Point) {671, 130}, perso_gris);
}

void afficher_score(Partie partie) {

    char score[14];
    sprintf(score, "SCORE : %05d", partie.pacman.score);
    afficher_texte(score, 18, (Point) {513, 190}, perso_grisclair);
}

void afficher_bonus(Partie partie) {
    // normal
    char bonus_normal[8];
    sprintf(bonus_normal, "%03d/%03d", partie.pacman.bonus.nbrDeBonusNormal, partie.bonus.nbrDeBonusNormal);
    afficher_texte(bonus_normal, 18, (Point) {493, 235}, perso_grisclair);

    // puissant
    char bonus_puissant[8];
    sprintf(bonus_puissant, "%03d/%03d", partie.pacman.bonus.nbrDeGommes, partie.bonus.nbrDeGommes);
    afficher_texte(bonus_puissant, 18, (Point) {656, 235}, perso_grisclair);
}

void afficher_pointsDeVie(Partie partie) {
    afficher_texte("POINTS DE VIE", 20, (Point) {499, 343}, perso_grisclair);

    Point pacman_icone_point[3] = {(Point) {573, 382}, (Point) {621, 382}, (Point) {669, 382}};

    for (int i = 0; i < 3; i++) {
        if (partie.pacman.nbrDeVies >= i + 1) {
            afficher_image("./images/panneau/pacman_icone_vie.bmp", pacman_icone_point[i]);
        } else {
            afficher_image("./images/panneau/pacman_icone_mort.bmp", pacman_icone_point[i]);
        }
    }
}

void afficher_etats(Partie partie) {
    // confusion
    long diff_confusion = (time(NULL) - partie.pacman.etat.estConfusTime);
    afficher_texte("CONFUS:", 15, (Point) {473, 496}, perso_grisclair);

    if (diff_confusion <= DUREE_CONFUSION_EN_S) {
        char confus[4];
        sprintf(confus, "'%02ld", DUREE_CONFUSION_EN_S - diff_confusion);
        afficher_texte(confus, 15, (Point) {576, 496}, perso_grisclair);
    } else {
        afficher_texte("NON", 15, (Point) {576, 496}, perso_grisclair);
    }

    // freeze des fantomes
    long diff_freeze = (time(NULL) - partie.fantomes[0].etat.estFreezeTime);
    afficher_texte("FREEZE:", 15, (Point) {473, 536}, perso_grisclair);

    if (diff_freeze <= DUREE_FREEZE_EN_S) {
        char freeze[4];
        sprintf(freeze, "'%02ld", DUREE_FREEZE_EN_S - diff_freeze);
        afficher_texte(freeze, 15, (Point) {576, 536}, perso_grisclair);
    } else {
        afficher_texte("NON", 15, (Point) {576, 536}, perso_grisclair);
    }

    long diff_destructo = (time(NULL) - partie.pacman.etat.estEnDestructoTime);
    afficher_texte("DESTRUCTO:", 15, (Point) {638, 503}, perso_grisclair);

    if (diff_destructo <= DUREE_DESTRUCTO_EN_S) {
        char destructo[4];
        sprintf(destructo, "'%02ld", DUREE_DESTRUCTO_EN_S - diff_destructo);
        afficher_texte(destructo, 15, (Point) {682, 529}, perso_grisclair);
    } else {
        afficher_texte("NON", 15, (Point) {682, 529}, perso_grisclair);
    }
}