// NIVEAU.C
// Ce fichier regroupe le chargement du plan provenant du fichier .txt, le chargement de la partie à partir du plan,
// ainsi que son déroulement, la récupération des tunnels de la carte et le dessin du plateau.

#include "niveau.h"

Partie charge_plan(char *fichier) {
    Partie p;
    FILE *f = fopen(fichier, "r"); // Ouverture en lecture du fichier
    p.plateau = NULL;   // Le futur plan, à allouer dynamiquement.
    int res, l, c;
    int nbf;        // Nb de fantômes trouvés sur le plan
    char ch;

    Bonus bonus = {0, 0};

    if (!f) // Si f== NULL, ouverture ratée
    {
        printf("Impossible d'ouvrir '%s'\n", fichier);
        exit(0);
    }

/* Lecture des dimensions du plan en en-tête                                  */
    res = fscanf(f, "%d %d\n", &p.L, &p.C); // Lecture de deux entiers

// Si on n'a pas pu lire deux entiers ou s'ils sont incorrects
    if (res != 2 || p.C < 2 || p.L < 2 || p.C > 800 || p.L > 600) {
        printf("Dimensions du tableau lues dans '%s' incorrectes\n", fichier);
        fclose(f);
        exit(0);
    }

    printf("Dimensions lues: %d x %d\n", p.L, p.C);

/* ALLOCATION DYNAMIQUE                                                       */
/* Allocation du tableau de *L pointeurs sur lignes                           */
    p.plateau = (char **) malloc(p.L * sizeof(char *));
    if (p.plateau == NULL) {
        printf("Allocation dynamique impossible\n");
        fclose(f);
        exit(0);
    }

/* Allocation des tableaux de *C caractères                                   */
    for (l = 0; l != p.L; l++) {
        p.plateau[l] = (char *) malloc(p.C * sizeof(char));
        if (p.plateau[l] == NULL) {
            printf("Allocation dynamique impossible\n");
            fclose(f);
            exit(0);
        }
    }

    l = 0;
    res = 0;
    nbf = 0;

    while (res != EOF) // Lecture de chaque ligne
    {
        c = 0;
        while (1) {
            res = fscanf(f, "%c", &ch); // Lecture d'un caractère
            if (res == EOF) // Si fin de fichier
                break; // Quittons la boucle interne

            if (c > p.C) // Si trop de colonnes...
            {
                printf("Ligne %d colonne %d: trop de colonnes\n", l, c);
                fclose(f);
                exit(0);
            }

            if (c == p.C) // Si fin de ligne supposée...
            {
                if (ch == '\n') // Si fin de ligne réelle, on quitte la boucle
                {
                    break;
                } else // Sinon trop de caractères
                {
                    printf("Ligne %d: trop de caractères\n", l);
                    fclose(f);
                    exit(0);
                }
            }
/* ...sinon, nous ne sommes pas à la fin de la ligne.                         */
/* Si on lit un caractère interdit...                                         */
            if (ch != '.' && ch != ' ' && ch != '*' && ch != 'P' && ch != 'F' && ch != 'B' && ch != 'C') {
                if (ch == '\n') // Si c'est un saut de ligne
                    printf("Ligne %d: trop peu de caractères\n", l);
                else
                    printf("Ligne %d: caractère '%c' incorrect\n", l, ch);

                fclose(f);
                exit(0);
            }

            if (ch == 'P') {
                p.pacman.pos.l = l;
                p.pacman.pos.c = c;
            } else if (ch == 'F') {
                if (nbf > 4) {
                    printf("Ligne %d:  un fantôme de trop!\n", l);
                    fclose(f);
                    exit(0);
                }
                p.fantomes[nbf].pos.l = l;
                p.fantomes[nbf].pos.c = c;
                p.fantomes[nbf].etat.estFreezeTime = 0;
                nbf++;
            } else if (ch == 'B')
                bonus.nbrDeGommes++;
            else if (ch == '.')
                bonus.nbrDeBonusNormal++;

            if (ch != 'P' && ch != 'F') {
                p.plateau[l][c] = ch; // Ecriture dans le plan
            }

            c++; // caractère suivant
        }
        l++; // ligne suivante
    }

    fclose(f); // Fermeture du flux de lecture du fichier

/* Si à la lecture de EOF on n'est pas sur la *V+1 ème ligne...               */
    if (l != p.L + 1) {
        printf("Ligne %d: nb de lignes incorrect\n", l);
        exit(0);
    }

/* Si nb de fantômes incorrect...                                             */
    if (nbf != 4) {
        printf("Nb de fantômes incorrect sur le plan\n");
        fclose(f);
        exit(0);
    }

    p.bonus.nbrDeBonusNormal = bonus.nbrDeBonusNormal;
    p.bonus.nbrDeGommes = bonus.nbrDeGommes;

    return p;
}

void dessiner_plateau(Partie p) {

    // Pour chaque case du plateau, s'il s'agit d'un élément de l'environnement, on le dessine
    // les dessins des personnages se fera à part car leur position n'est pas stocké sur le plateau
    for (int l = 0; l < p.L; l++) {
        for (int c = 0; c < p.C; c++) {
            char symbole = p.plateau[l][c];
            if (symbole == '*') {
                afficher_image("./images/environnement/mur.bmp", pos2point((Pos) {l, c}));
            } else if (symbole == '.') {
                afficher_image("./images/environnement/bonus.bmp", pos2point((Pos) {l, c}));
            } else if (symbole == 'B') {
                afficher_image("./images/environnement/bonus_puissant.bmp", pos2point((Pos) {l, c}));
            }
        }
    }
}

void recuperer_liste_tunnels(Partie *p) {

    int nombreDeTunnels = 0;

    // Parcours de toutes les cases du plateau
    for (int ligne = 0; ligne < p->L; ligne++) {
        for (int colonne = 0; colonne < p->C; colonne++) {
            // Si la case se situe sur la ligne tout en haut, tout à gauche, tout en bas ou tout à droite
            if (position_est_un_contour(*p, (Pos) {ligne, colonne})) {
                // Si à la position du plateau se trouve du vide ou un bonus, celle ci est considérée comme un tunnel
                if (p->plateau[ligne][colonne] == ' ' || p->plateau[ligne][colonne] == '.') {
                    p->tunnels.tunnel[nombreDeTunnels] = (Pos) {ligne, colonne};
                    nombreDeTunnels++;
                }
            }
        }
    }

    p->tunnels.nbrDeTunnels = nombreDeTunnels;
}

void charge_partie(Partie *p) {

    // On initialise pacman avec des valeurs par défaut permettant le bon fonctionnement de pacman et du niveau
    initialiser_pacman(&p->pacman);

    dessiner_rectangle((Point) {0, 0}, MAXH, MAXV, noir);
    dessiner_plateau(*p);
    recuperer_liste_tunnels(p);
    actualiser();

    // on crée un pointeur vers les évènements de SDL afin de les utiliser
    p->events = recuperer_pointeur_evenements();

    // les conditions pour que pacman passe au niveau suivant et casse la boucle d'un niveau sont
    // qu'il ait perdu tous ses points de vie ou qu'il ait mangé tous les bonus
    while (p->pacman.nbrDeVies > 0 && !a_mange_tous_les_bonus(*p)) {
        // Mode non bloquant à l'aide des évènements
        traiter_evenements();
        deplacer_pacman(p, 0);
        // Si les fantomes ne sont pas "freeze" à cause d'un bonus puissant, nous les déplaçons
        if (time(NULL) - p->fantomes[0].etat.estFreezeTime > DUREE_FREEZE_EN_S) {
            deplacer_fantomes(p);
        }
        // On réinitialise les évènements pour traiter les nouveaux, ceux qui vont survenir lors du prochain tour.
        reinitialiser_evenements();
        // Affichage des statistiques en jeu (panneau de droite)
        afficher_stats(*p);
        attente(400);
    }
}

