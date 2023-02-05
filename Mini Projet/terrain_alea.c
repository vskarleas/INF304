#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "terrain.h"

int alea_borne(int borne_inf, int borne_sup)
{
    return (rand() % (borne_sup - borne_inf + 1)) + borne_inf;
}

int alea_piece()
{
    return alea_borne(0, 1);
}

int alea_de()
{
    return alea_borne(1, 6);
}

void terrains_alea(int n, int l, int h, float d, int graine, char* nom_f_terrains)
{
    srand(graine);
    int nb_terrains_valides = 0;
    float densite_actuelle;
    float densite_totale = 0.0;
    Terrain *t;
    FILE *f = fopen(nom_f_terrains, "w");
    fprintf(f, "%d\n", n);
    int x, y, nb_cases_restantes, X2;
    for (int k = 0; k < n; k++)
    {
        t = malloc(sizeof(Terrain));
        init_terrain(t);
        t->largeur = l;
        t->hauteur = h;
        nb_cases_restantes = l * h - 1;
        X2 = d * l * h;
        x = l / 2; // alea_borne(0, l - 1);
        y = h / 2; // alea_borne(0, h - 1);

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
                                t->tab[i][j] = ROCHER;
                            }
                            else
                            {
                                t->tab[i][j] = EAU;
                            }
                            X2--;
                        }
                        nb_cases_restantes--;
                    }
                }
            }
        }
        if (est_terrain_valide(t, x, y))
        {
            nb_terrains_valides++;
            fprintf(f, "******************************** Terrain valide ********************************\n");
        }
        else
        {
            fprintf(f, "******************************* Terrain invalide *******************************\n");
        }
        densite_actuelle = densite(t);
        densite_totale += densite_actuelle;
        fprintf(f, "Densité attedue : %f\n", d);
        fprintf(f, "Densité réelle : %f\n", densite_actuelle);
        ecrire_terrain(f, t, x, y);
        free(t);
        fprintf(f, "\n\n");
    }
    float densite_moyenne = densite_totale / (float)n;
    fprintf(f, "Densite moyenne : %f\n", densite_moyenne);
    float pourcentage_terrains_valides = (float)nb_terrains_valides / (float)n * 100.0;
    fprintf(f, "Pourcentage de terrains valides : %f%%\n", pourcentage_terrains_valides);
    fprintf(f, "Nombre de terrains valides : %d\n", nb_terrains_valides);
    fclose(f);
}

void test()
{
    int l, h;
    float d;
    scanf("%d", &l);
    scanf("%d", &h);
    scanf("%f", &d);
    int n = alea_borne(10, 30);
    terrains_alea(n, l, h, d, time(NULL), "terrains_alea.txt");
}