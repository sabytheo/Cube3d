Heading
=======
Sub-heading
-----------
# Alternative heading
## Alternative sub-heading
Text attributes _italic_, **bold**, `monospace`.

----------------------------------------------------------------------

Notion [https://www.notion.so/Cub3d-1d21ecf7d7e080cb82d0d190dbe112e7]

PARSING
==============

FONCTION parse_map(filename):
-------------------------------
OUVRIR le fichier
LIRE ligne par ligne
VALIDER le format (.cub)
EXTRAIRE textures (NO, SO, WE, EA)
EXTRAIRE couleurs (F, C)
CONSTRUIRE la grille 2D
TROUVER position joueur
VALIDER que la map est fermée
	flood fill into check si autour de f il y a un 1 ou un f sinon NOT GOOD
recreer map.
RETOURNER structure Map


Résumé des notions pour le projet Cub3D
Voici toutes les notions mathématiques et techniques à maîtriser pour réussir le projet Cub3D :
1. Concepts Mathématiques Géométriques
Repères et Coordonnées

Repère 3D orthonormé (axes x, y, z perpendiculaires)
Points : P(x, y, z)
Vecteurs : direction avec coordonnées (x, y, z)

Plans

Équation de plan : ax + by + cz + d = 0
Plans horizontaux et verticaux pour représenter les murs
Vecteur normal au plan : (a, b, c)

Droites et Rayons

Équation paramétrique de droite
Demi-droite (rayon) : droite finie d'un côté
Paramètre t pour calculer les intersections

Trigonométrie

Cosinus, Sinus, Tangente (CAH SOH TOA)
Conversion degrés → radians : radian = degré × π / 180
Angles en radians pour les calculs

2. Création de la Caméra (Rayons)
FOV (Field of View)

Définir le champ de vision (recommandé : 60° ou π/3 radians)
Créer un rayon par pixel de l'écran (W × H rayons)

Répartition et Correction Fish-Eye

Répartition planaire : distances constantes entre rayons
Calcul des ratios horizontal (R_H) et vertical (R_V)
Formules :

R_H = 2 × tan(FOV/2) / W
R_V = 2 × tan(FOV × H / (W × 2)) / H



Génération des Rayons

Créer les rayons avec orientation Nord par défaut
Formule : ((i - W×0.5)×R_H, -1, (H×0.5 - j)×R_V)
Normalisation des vecteurs (optionnel pour bonus)

3. Création de la Map (Plans)
Murs

Plans verticaux : x = constante → x - d = 0
Plans horizontaux : y = constante → y - d = 0
Organisation en 4 tableaux (N, S, E, W)

Sprites

Plan perpendiculaire au vecteur caméra-sprite
Vecteur v = S - O (sprite - origine)
Équation : vx×x + vy×y + 0×z + d = 0

Sol et Plafond (Bonus)

Sol : {0, 0, 1, 0}
Plafond : {0, 0, 1, -1}

4. Raycasting (Intersections)
Calcul d'Intersection Droite-Plan

Formule principale : t = -(aOx + bOy + cOz + d) / (aux + buy + cuz)
Point d'intersection : I = O + u × t
Vérifications :

t > 0 (devant la caméra)
0 ≤ Iz < 1 (hauteur du mur)



Checks Cardinaux

Nord : case (Ix, -d-1)
Sud : case (Ix, -d)
Est : case (-d, Iy)
Ouest : case (-d-1, Iy)

5. Matrices de Rotation
Matrices 2D et 3D

Matrice de rotation Z (tourner sur soi-même)
Matrice de rotation X (regarder haut/bas - bonus)
Matrice de rotation Y (tangage - bonus)

Application

Multiplier la matrice par les vecteurs de rayons
Formules avec cos(θ) et sin(θ)

6. Textures
Murs

Partie décimale de Ix et Iz (axe x)
Partie décimale de Iy et Iz (axe y)

Sprites

Ratio r pour la largeur
Partie décimale de Iz pour la hauteur
Vérifier 0 ≤ r < 1

Sol/Plafond (Bonus)

Parties décimales de Ix et Iy

7. Calculs Vectoriels

Addition : w = (ux+vx, uy+vy, uz+vz)
Soustraction : w = (ux-vx, uy-vy, uz-vz)
Multiplication scalaire : w = (ux×k, uy×k, uz×k)
Produit scalaire : u·v = ux×vx + uy×vy + uz×vz
Norme : |u| = √(ux² + uy² + uz²)
Normalisation : u = u / |u|

8. Optimisations
Précalcul

Rayons avant la boucle graphique
Plans constants
Sprites une fois par frame

Minimisation

Supprimer les murs inutiles
Trier les sprites par distance
Simplifier les calculs (éliminer paramètres nuls)

Bonnes Pratiques

Éviter les divisions : remplacer par multiplications
Stocker les angles en radians
Minimiser les fonctions mathématiques (sqrt, cos, sin, tan)
Préférer tableaux aux listes chaînées

9. Bonus Recommandés

Collisions et slide (glissement sur murs)
Multithreading (répartir calculs sur plusieurs cœurs)
HUD (optimise en réduisant pixels calculés)
Pénombre (distance de vue)
Scale de rendu (diviser résolution par 4)
Gravité : d = √(2g(z₀-z)) / FPS
Skybox (6 plans formant un cube)
Transparence des sprites
Raytracing (sources de lumière)

10. Points d'Attention

Angles toujours en radians
Division plus lente que multiplication
Normaliser les vecteurs pour certains calculs
Gérer les imprécisions de cast en int
FPS : optimiser pour 60+ frames/seconde
