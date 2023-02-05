#include "environnement.h"
#include "interprete.h"
#include "terrain.h"
#include "programme.h"
int main (int argc, char **argv){
    Terrain t;
    Programme p;
    Robot r;
    Environnement e;
    resultat_inter re = OK_ROBOT;
    etat_inter ei;
    ei.pc = 0;
    int x, y;
    FILE *f = fopen(argv[1], "r");
    lire_terrain(f, &t, &x, &y);
    init_robot(&r, x, y, Est);
    printf("Robot - Position : (%d, %d) - Orientation : ", x, y);
    e.r = r;
    e.t = t;
    lire_programme(&p, argv[2]);
    while(re == OK_ROBOT)
    {
        afficher_envt(&e);
        re = exec_pas(&p, &e, &ei);
    }
    afficher_envt(&e);
    switch (re)
    {
    case OK_ROBOT:
        printf("Robot sur une case libre, programme non terminé (ne devrait pas "
               "arriver)\n");
        break;
    case SORTIE_ROBOT:
        printf("Le robot est sorti :-)\n");
        break;
    case ARRET_ROBOT:
        printf("Robot sur une case libre, programme terminé :-/\n");
        break;
    case PLOUF_ROBOT:
        printf("Le robot est tombé dans l'eau :-(\n");
        break;
    case CRASH_ROBOT:
        printf("Le robot s'est écrasé sur un rocher X-(\n");
        break;
    case ERREUR_PILE_VIDE:
        printf("ERREUR : pile vide\n");
        break;
    case ERREUR_ADRESSAGE:
        printf("ERREUR : erreur d'adressage\n");
        break;
    case ERREUR_DIVISION_PAR_ZERO:
        printf("ERREUR : division par 0\n");
        break;
    }
}