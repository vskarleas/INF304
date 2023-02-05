#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "es_tableau.h"
#include "test_tri.h"
#include "tri.h"
#include "type_tableau.h"

int main(int argc, char **argv) {

  tableau_entiers t;
  FILE *ftab;
  char nom_fichier[256];

  if (argc < 2) {
    printf("Usage: %s <fichier d'entree>\n", argv[0]);
  } else {
    /* a modifier pour les exercices 3 a 6 */
    lire_tableau(argv[1], &t);
    tri_insertion(&t);
    strcpy(nom_fichier, argv[1]);
    strcat(nom_fichier, ".out");
    ecrire_tableau(nom_fichier, &t);
    test_tri_insertion(argc, argv);
    test_tri_insertion_alea(argc, argv);
  }
}
