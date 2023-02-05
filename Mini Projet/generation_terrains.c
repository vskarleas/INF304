#include "generation_terrains.h"
#include "terrain_alea.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Génère aléatoirement un terrain T, de largeur l, de hauteur h,
   avec une densité d'obstacle dObst : 0 <= dObst <= 1.
   Précondition : T est un pointeur vers un terrain existant.
   Résultat : T est modifié et contient le terrain généré.
              La case centrale de T ne contient pas d'obstacle.
 */
void generation_aleatoire(Terrain *T, int l, int h, float dObst)
{
    int x, y, nb_cases_restantes, X2;
    T->largeur = l;
    T->hauteur = h;
    nb_cases_restantes = l * h - 1;
    X2 = dObst * l * h;
    x = h / 2; // alea_borne(0, l - 1);
    y = l / 2; // alea_borne(0, h - 1);

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (true || X2 != 0)
            {
                if (j != x || i != y)
                {
                    if (alea_borne(1, nb_cases_restantes) <= X2)
                    {
                        if (alea_piece())
                        {
                            T->tab[i][j] = ROCHER;
                        }
                        else
                        {
                            T->tab[i][j] = EAU;
                        }
                        X2--;
                    }
                    nb_cases_restantes--;
                }
            }
        }
    }
}

// determine s'il existe un chemin du centre au bord du terrain T
// version avec tableau annexe
int existe_chemin_vers_sortie(Terrain *T)
{

    int l = largeur(T);
    int h = hauteur(T);
    int chemin_trouve = 0;
    int i;
    // tableau de marque
    // initialisation
    //   marque(x,y) = 0 <=> la case est libre et non marquee
    //   marque(x,y) = 3 <=> la case est occupee (eau/roche)
    // boucle
    //   marque(x,y) = 0 <=> la case est libre et non marquee
    //   marque(x,y) = 1 <=> la case est libre, marquee et non traitee
    //   marque(x,y) = 2 <=> la case est libre, marquee et traitee
    //   marque(x,y) = 3 <=> la case est occupee

    //
    int marque[DIM_MAX][DIM_MAX];
    int x, y, x1, y1;
    int existe_case_1;

    // initialiser le tableau marque
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < l; x++)
        {
            if (est_case_libre(T, x, y))
            {
                marque[x][y] = 0;
            }
            else
            {
                marque[x][y] = 3;
            }
        }
    }
    // marquer la seule case centrale
    x = l / 2;
    y = h / 2;
    marque[x][y] = 1;

    // boucle de recherche du chemin : trouver un ensemble connexe
    // de cases (marquées 1 ou 2) contenant la case centrale et
    // une case de bord
    existe_case_1 = 1;
    while (existe_case_1 && !chemin_trouve)
    {
        // rechercher une case libre, marquee et non traitee
        existe_case_1 = 0;
        x = 0;
        y = 0;
        while (y < h && !existe_case_1)
        {
            if (marque[x][y] == 1)
            {
                // la case (x,y) est marquée 1
                existe_case_1 = 1;
            }
            else
            {
                // passer à la case suivante
                x++;
                if (x >= l)
                {
                    x = 1;
                    y++;
                }
            }
        }

        if (existe_case_1)
        {
            // marquer la case (x,y) comme marquee et traitee
            marque[x][y] = 2;

            // rechercher les cases voisines de (x,y) non marquees (0)
            // et pour chaque case voisine (x1,y1) vide et non marquee,
            // si c'est une case de bord,
            //   mettre le booleen chemin_trouve a VRAI
            // sinon
            //  la marquer (1,x,y) et l'empiler
            for (i = 0; i < 4; i++)
            {
                switch (i)
                {
                case 0:
                    x1 = x;
                    y1 = y + 1;
                    break;
                case 1:
                    x1 = x;
                    y1 = y - 1;
                    break;
                case 2:
                    x1 = x + 1;
                    y1 = y;
                    break;
                case 3:
                    x1 = x - 1;
                    y1 = y;
                    break;
                default:
                    break;
                }
                if (x1 < l && y1 < h && marque[x1][y1] == 0)
                {
                    marque[x1][y1] = 1;
                    if (x1 == 0 || x1 == l - 1 || y1 == 0 || y1 == h - 1)
                    {
                        chemin_trouve = 1;
                    }
                }
            }
        }
    }
    return chemin_trouve;
}