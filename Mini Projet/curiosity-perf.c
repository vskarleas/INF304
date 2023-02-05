#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "terrain_alea.h"
#include "terrain.h"
#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "generation_terrains.h"

#define TENTATIVES_MAX 1000000

#define eprintf(...) fprintf(stderr, __VA_ARGS__)

int main(int argc, char **argv)
{
    erreur_programme errp;
    etat_inter etat;
    resultat_inter res;

    /* Vérification du nombre d'arguments */
    if (argc < 8)
    {
        eprintf("Pas assez d'arguments.");
        return EINVAL;
    }

    /* Récupération des arguments */
    char *nom_f_programme = argv[1];
    int n;
    sscanf(argv[2], "%d", &n);
    int l;
    sscanf(argv[3], "%d", &l);
    int h;
    sscanf(argv[4], "%d", &h);
    float d = atof(argv[5]);
    int graine;
    sscanf(argv[6], "%d", &graine);
    int nb_step_max;
    sscanf(argv[7], "%d", &nb_step_max);
    char *nom_f_res = argv[8];

    // test de l et h
    if (l > DIM_MAX || l % 2 == 0)
    {
        printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
        return 1;
    }
    if (h > DIM_MAX || h % 2 == 0)
    {
        printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
        return 1;
    }
    if ((d > 1) || (d < 0))
    {
        printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
        return 1;
    }

    /* Lecture du programme */
    Programme prog;

    /* Mise en place de la graine */
    srand(graine);

    /*
        char nom_f_terrains[] = "terrains_alea.txt";

        terrains_alea(n, l, h, d, graine, nom_f_terrains);*/

    /* Création du fichier de resultat */
    FILE *f_res = fopen(nom_f_res, "w");
    fprintf(f_res, "Nombre de terrains testés : %d\nDimensions des terrains : %dx%d\nDensité d'obstacle : %f\n", n, l, h, d);

    Terrain t;
    Robot r;
    Environnement envt;
    int nb_pas;
    int robot_sorti = 0;
    int robot_bloque = 0;
    int robot_plouf = 0;
    int robot_crash = 0;
    int nb_pas_sorti_total = 0;

    for (int i = 0; i < n; i++)
    {
        errp = lire_programme(&prog, nom_f_programme);
        init_terrain(&t);
        generation_aleatoire(&t, l, h, d);
        int j;
        for (j = 0; !existe_chemin_vers_sortie(&t) && j < TENTATIVES_MAX; j++)
        {
            init_terrain(&t);
            generation_aleatoire(&t, l, h, d);
        }

        //afficher_envt(&envt);
        if (j == TENTATIVES_MAX)
        {
            eprintf("Terrain valide impossible a générer.\n");
            exit(1);
        }
        r.x = l / 2;
        r.y = h / 2;
        r.o = Est;
        envt.t = t;
        envt.r = r;

        /* Initialisation de l'état */
        init_etat(&etat);
        res = OK_ROBOT;
        for (nb_pas = 0; res == OK_ROBOT && nb_pas < nb_step_max; nb_pas++)
        {
            res = exec_pas(&prog, &envt, &etat);
            /* Affichage du terrain et du robot */
            // afficher_envt(&envt);
        }
        switch (res)
        {
        case OK_ROBOT:
            robot_bloque++;
            break;
        case SORTIE_ROBOT:
            robot_sorti++;
            nb_pas_sorti_total += nb_pas;
            break;
        case PLOUF_ROBOT:
            robot_plouf++;
            break;
        case CRASH_ROBOT:
            robot_crash++;
            break;
        default:
            robot_bloque++;
            break;
        }/*
        if (res == SORTIE_ROBOT)
        {
            fprintf(f_res, "******************************** Terrain valide ********************************\n");
            ecrire_terrain(f_res, &t, l / 2, h / 2);
        }
        else
        {
            fprintf(f_res, "******************************* Terrain invalide *******************************\n");
            ecrire_terrain(f_res, &t, l / 2, h / 2);
        }*/
        printf("%d\n", i);
    }

    fprintf(f_res, "\n");

    float pourcentage_robot_bloque = (float)robot_bloque / (float)n * 100;
    fprintf(f_res, "Le robot est resté bloqué %f%% du temps soit %d fois.\n\n", pourcentage_robot_bloque, robot_bloque);

    float pourcentage_robot_sorti = (float)robot_sorti / (float)n * 100;
    float moyenne_pas = (float)nb_pas_sorti_total / (float)robot_sorti;
    fprintf(f_res, "Le robot est sorti %f%% du temps soit %d fois. Il a fait en moyenne %f pas.\n\n", pourcentage_robot_sorti, robot_sorti, moyenne_pas);

    float pourcentage_robot_plouf = (float)robot_plouf / (float)n * 100;
    fprintf(f_res, "Le robot est tombé dans l'eau %f%% du temps soit %d fois.\n\n", pourcentage_robot_plouf, robot_plouf);

    float pourcentage_robot_crash = (float)robot_crash / (float)n * 100;
    fprintf(f_res, "Le robot s'est écrasé contre un rocher %f%% du temps soit %d fois.\n\n", pourcentage_robot_crash, robot_crash);

    fclose(f_res);
}