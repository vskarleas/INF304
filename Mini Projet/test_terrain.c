#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv)
{
  FILE *f;
  Terrain t;
  int x, y;
  char nom_fichier[256];

  if (argc < 2)
  {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  erreur_terrain valeur_erreur = lire_terrain(f, &t, &x, &y);
  while (valeur_erreur == ERREUR_FICHIER)
  {
    printf("Fichier invalide!\n\t");
    scanf("%s", nom_fichier);
    f = fopen(nom_fichier, "r");
    valeur_erreur = lire_terrain(f, &t, &x, &y);
  }
  switch (valeur_erreur)
  {
  case ERREUR_DIMENSION:
    printf("ERREUR_DIMENSION\n");
    break;
  case ERREUR_FORMAT:
    printf("ERREUR_FORMAT\n");
    break;
  case ERREUR_ROBOT_ABSENT:
    printf("ERREUR_ROBOT_ABSENT\n");
    break;
  case OK:
    printf("OK\n");
    break;
  default:
    printf("AAAAAAAAAAAAAAAAAA");
  }
  fclose(f);
  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);
}