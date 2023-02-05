
#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) //x et y sont des pointers. Alors sur l'initilisation du terrain on a besoin de mettre l'etoile (*) au debut [EX: *x=rx; *y=ry]
{
    int l, h;   // Dimensions du terrain
    int rx, ry; // Coordonnées initiales du robot

    if (f == NULL)
    {
        return ERREUR_FICHIER;
    }

    char c;

    // Lecture de la largeur
    fscanf(f, "%d", &l);

    // Lecture de la hauteur
    fscanf(f, "%d", &h);

    // Lecture du terrain
    fscanf(f, "%c", &c);
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (c != '/n')
            {
                t->tab[i][j] = c;
                fscanf(f, "%c", c);
            }
            else
            {
                fscanf(f, "%c", c);
            }
        }
    }

    // Initialisation de la position du robot
    t->largeur = l;
    t->hauteur = h;

    return OK;
}

/* À compléter */
