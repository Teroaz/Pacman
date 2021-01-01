## Projet PACMAN : DUT INFO S1 - IUT

### Groupe : Scharan & Philippe (Noms retirés)


##### Pour notre projet de premier semestre, nous avons eu à développer un pacman en langage C.


## Introduction
Pacman est un jeu 2D composé d'un personnage jaune (Pacman) qui doit manger des bonus en étant poursuivi par des fantômes qui essayeront de le manger.

# Compilation et exécution

` • make clean all : compiler le jeu en nettoyant les anciens fichiers compilés`

`• ./resultat : accéder à l'écran d'accueil du jeu`

# Travail accompli

Pour ce projet Pacman, nous avons évidémment tenté de reproduire le jeu original en y apportant notre touche.


### Pacman
- Pour passer au niveau supérieur Pacman doit manger tous les bonus normaux (rapportant 1 point) et tous les bonus puissants (rapportant 20 points et gêlant tous les fantomes durant 5 secondes, les rendant vulnérables). Au dernier niveau, c'est la victoire du joueur.
- Pacman peut se retrouver confus durant 5 secondes s'il passe un à travers un tunnel de la carte et peut passer en mode "Destructo" durant 20 secondes s'il mange tous les bonus puissants.

*Confusion : inverse le sens de déplacement sélectionné par le joueur*

*Destructo : transformation qui permet de casser les murs, créer des tunnels si nous avançons en ligne droite, rendant également Pacman invulnérable aux fantomes qu'il pourra manger pour gagner (10 points)*

- Si Pacman ne se déplace pas manuellement, il le sera automatiquement en suivant le dernier sens auquel se dirigeait le joueur.


### Fantomes
- Les fantomes vont vouloir s'emparer de pacman tout en possédant divers comportements : certes ils sont tous "rouges" mais 2 des 4 vont se rapprocher de pacman en se déplaçant sur les cases environnantes qui leur permettront d'accéder plus rapidement à la position de Pacman, un autre va se déplacer en recopiant le sens que prend pacman et le dernier va faire la même en recopiant cette fois-ci le sens inverse.


### Partie
- Tout d'abord le jeu est en non-bloquant, les fantomes se déplaceront même si le joueur ne se déplace pas manuellement.
- Le jeu possède un système de menu principal permettant de faire jouer les 3 niveaux disponibles à la suite et afficher différents écrans selon si le joueur a perdu, gagné ou est passé au niveau supérieur.
- A chaque lancement d'un niveau, le jeu va rechercher tous les tunnels disponibles permettant ainsi un certain dynamisme de la disposition des tunnels pour chaque niveau.


# Problèmes rencontrés / obstacles :

- Pour les fantômes, nous voulions faire un algorithme de plus-court-chemin, mais ce dernier nous semblait complexe, nous avons donc choisi d'utiliser des algorithmes dits "naifs".


# Bugs connus :  
Les seuls bugs connus et qui n'ont pas eu le temps d'être traités sont en lien avec les fantomes.

- Les fantomes peuvent se superposer, le principal problème est que si plusieurs fantomes superposés vont en même temps sur Pacman alors qu'il est vulnérable, il perdra 1 point de vie pour chaque fantome.
