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
