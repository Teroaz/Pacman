// MENU_PRINCIPAL.C
// Ce fichier regroupe la gestion de niveau qui se succèdent et la prise en charge de l'écran d'accueil,
// des écrans de victoire et de défaite ainsi que la transition entre chaque niveau

#include "menu_principal.h"

// Tableau des cartes qui vont être jouées au fur et à mesure de la partie
char *plans[NBR_DE_MAPS] = {"./data/niveau1.txt", "./data/niveau2.txt", "./data/niveau3.txt"};

void lancer_jeu(int firstStart) {

    // après une victoire ou une défaite, on peut décider de rappeller cette fonction, en définissant
    // firstStart à 0, ce qui permet de ne pas ouvrir une fenêtre et ne pas passer par l'écran d'accueil
    // pour directement commencer à rejouer, depuis le main.c, la fonction est lancée avec firstStart = 1

    if (firstStart) {
        ouvrir_fenetre(MAXH, MAXV);
        ecran_daccueil();
    }

    int score_total = 0;

    // boucle qui va englober chaque niveau et gérer les différents cas de la partie
    // défaite / passage niveau supérieur / victoire (gain de tous les niveaux)

    for (int i = 0; i < NBR_DE_MAPS; i++) {
        Partie p = charge_plan(plans[i]);
        p.niveau = i + 1;
        p.timestamp = time(NULL);
        charge_partie(&p);
        score_total += p.pacman.score;

        if (p.pacman.nbrDeVies <= 0) {
            // Pacman a perdu toute sa vie -> Défaite
            fin_partie(score_total, 0);
        } else if (a_mange_tous_les_bonus(p) && p.niveau == NBR_DE_MAPS) {
            // Pacman a mangé tous les bonus et le niveau actuel était le dernier
            fin_partie(score_total, 1);
        } else {
            // transition au niveau supérieur en attendant un clic du joueur
            passage_niveau_superieur(p.niveau);
            attendre_clic();
        }
    }

    actualiser();
    attendre_clic();
    fermer_fenetre();
}


void ecran_daccueil() {

    afficher_image("./images/ecran_accueil.bmp", (Point) {0, 0});
    actualiser();

    // tant que le bouton "jouer" ou "quitter" n'est pas pressé, nous ne faisons rien
    do {
        Point coords = attendre_clic();
        if ((coords.x >= 277 && coords.x <= 527) && (coords.y >= 392 && coords.y <= 470)) { // "Jouer"
            break;
        } else if ((coords.x >= 346 && coords.x <= 458) && (coords.y >= 494 && coords.y <= 512)) { // "Quitter"
            exit(0); // fermeture du processus
        }
    } while (1);

}

// écran de transition entre chaque niveau (pour le passage au niveau supérieur)
void passage_niveau_superieur(int niveau_actuel) {

    afficher_image("./images/passage_niv_suivant.bmp", (Point) {0, 0});

    afficher_texte("VOUS AVEZ COLLECTIONNE TOUS LES BONUS", 19, (Point) {45, 126}, perso_grisclair);
    afficher_texte("PASSAGE AU NIVEAU SUPERIEUR...", 19, (Point) {112, 151}, perso_grisclair);

    char transition_texte[19];
    sprintf(transition_texte, "NIV %d -----> NIV %d", niveau_actuel, niveau_actuel + 1);
    afficher_texte(transition_texte, 24, (Point) {180, 287}, perso_bleuclair);

    afficher_texte("APPUYER POUR ACCEDER", 24, (Point) {156, 441}, perso_grisclair);
    afficher_texte("AU NIVEAU SUPERIEUR", 24, (Point) {169, 479}, perso_grisclair);
    actualiser();

}

// fin de partie est appelé avec un argument différent selon si c'est une défaite ou une victoire de tous les niveaux
// pareil que pour la fonction ecran_d'accueil, nous avons un bouton "rejouer" et "quitter"
void fin_partie(int score_total, int victoire) {

    if (victoire) {
        afficher_image("./images/ecran_victoire.bmp", (Point) {0, 0});
    } else {
        afficher_image("./images/ecran_defaite.bmp", (Point) {0, 0});
    }

    char score[14];
    sprintf(score, "SCORE : %05d", score_total);
    afficher_texte(score, 20, (Point) {47, 186}, perso_blancjaune);

    actualiser();

    do {
        Point coords = attendre_clic();
        if ((coords.x >= 277 && coords.x <= 527) && (coords.y >= 392 && coords.y <= 470)) {
            lancer_jeu(0); // pour relancer le jeu sans passer par l'écran d'accueil et réouvrir une fenêtre
            break;
        } else if ((coords.x >= 346 && coords.x <= 458) && (coords.y >= 494 && coords.y <= 512)) {
            exit(0);
        }
    } while (1);
}