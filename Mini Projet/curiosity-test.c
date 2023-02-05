#include <stdio.h>
#include <stdlib.h>
#include "environnement.h"
#include "interprete.h"
#include "terrain.h"
#include "programme.h"
#include <stdbool.h>

int main(int argc, char **argv)
{
    FILE *f_test = fopen(argv[1], "r");
    char nom_f_terrain[512];
    char c;
    fscanf(f_test, "%c", &c);
    for (int i = 0; c != '\n'; i++)
    {
        nom_f_terrain[i] = c;
        fscanf(f_test, "%c", &c);
    }
    char nom_f_programme[512];
    fscanf(f_test, "%c", &c);
    int i;
    for (i = 0; c != '\n'; i++)
    {
        nom_f_programme[i] = c;
        fscanf(f_test, "%c", &c);
    }
    nom_f_programme[i] = '\0';

    FILE *f_terrain = fopen(nom_f_terrain, "r");

    int nb_max_pas;
    fscanf(f_test, "%d\n", &nb_max_pas);
    char sortie_attendue;
    fscanf(f_test, "%c", &sortie_attendue);

    Terrain t;
    Programme p;
    Robot r;
    Environnement e;
    resultat_inter re = OK_ROBOT;
    etat_inter ei;
    ei.pc = 0;
    int x, y;
    lire_terrain(f_terrain, &t, &x, &y);
    init_robot(&r, x, y, Est);
    e.r = r;
    e.t = t;
    lire_programme(&p, nom_f_programme);
    printf("%d\n", nb_max_pas);
    for (int i = 0; i < nb_max_pas && re == OK_ROBOT; i++)
    {
        //afficher_envt(&e);
        re = exec_pas(&p, &e, &ei);
    }
    //afficher_envt(&e);
    char sortie;
    switch (re)
    {
    case OK_ROBOT:
        sortie = 'N';
        break;
    case SORTIE_ROBOT:
        sortie = 'S';
        break;
    case ARRET_ROBOT:
        sortie = 'F';
        break;
    case PLOUF_ROBOT:
        sortie = 'P';
        break;
    case CRASH_ROBOT:
        sortie = 'O';
        break;
    default:
        sortie = 'E';
    }

    if (sortie != sortie_attendue)
    {
        fprintf(stderr, "Le robot n'a pas fini dans le bon etat.\n\tEtat attendu : %c\n\tEtat atteint : %c\n", sortie_attendue, sortie);
        return 1;
    }
    if (sortie_attendue == 'N' || sortie_attendue == 'F')
    {
        int position_x, position_y;
        char orientation_attendue;
        fscanf(f_test, "%d %d\n%c", &position_x, &position_y, &orientation_attendue);
        if (!(e.r.x == position_x && e.r.y == position_y))
        {
            fprintf(stderr, "Le robot ne s'est pas arrete a la bonne position.\n\tPosition attendue : (%d,%d)\n\tPosition atteinte : (%d,%d)\n", position_x, position_y, e.r.x, e.r.y);
            return 2;
        }
        char orientation;
        switch (e.r.o)
        {
        case Nord:
            orientation = 'N';
            break;
        case Est:
            orientation = 'E';
            break;
        case Ouest:
            orientation = 'O';
            break;
        case Sud:
            orientation = 'S';
            break;
        }
        if (!(orientation_attendue == orientation))
        {
            fprintf(stderr, "Le robot n'a pas la bonne orientation.\n\tOrientation attendue : %c\n\tOrientation atteinte : %c\n", orientation_attendue, orientation);
            return 3;
        }
    }
    printf("OK!\n");
    return 0;
}