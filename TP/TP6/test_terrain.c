#include "terrain.h"
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r"); //exercise 2.2 on doit ajouter ici
  int id=1;
  char *nouveau_nom_fichier;
  while(id != 0) //sur le program final il y a un while tres interesant
  {
    if (f == NULL){
        printf("On ne pourrait pas ouvrir le fichier. Donner un autre fichier\n");
        scanf("%s", nouveau_nom_fichier);

        f = fopen(nouveau_nom_fichier, "r");
        id = 0;
    }
    else
    {
        id =0;
    }
  }
  lire_terrain(f, &t, &x, &y);
  fclose(f);
  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);
}
