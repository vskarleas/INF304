#include "commandes_calculette.h"
#include "type_pile.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    FILE *fichier = NULL;
    if (argc != 2){
        fprintf(stderr, "No correct argument file");
    }
    fichier = ouvrir_commandes(argv[1]);
    PileEntiers p;
    creer_pile(&p);

    commande command;

    int result;
    int x;
    int y;

    while (!fin_commandes(fichier)) {
    command = commande_suivante(fichier);
    print_commandes(command);
    switch (command.cmd) {
    case VIDER_PILE:
      vider(&p);
      break;
    case DEPILER_SOMMET:
      depiler(&p);
      break;
    case EMPILER_VALEUR:
      empiler(&p, command.arg);
      break;
    case EFFECTUER_ADDITION:
      x = depiler(&p);
      y = depiler(&p);
      result = x + y;
      empiler(&p, result);
      break;
    case EFFECTUER_SOUSTRACTION:
      x = depiler(&p);
      y = depiler(&p);
      result = y - x;
      empiler(&p, result);
      break;
    case EFFECTUER_MULTIPLICATION:
      x = depiler(&p);
      y = depiler(&p);
      result = y * x;
      empiler(&p, result);
      break;
    case EFFECTUER_DIVISION:
      x = depiler(&p);
      y = depiler(&p);
      result = y / x;
      empiler(&p, result);
      break;
    case COMMANDE_INCORRECTE:
      printf("Commande incorrecte !\n");
      break;
    }
    print(&p);
    printf("\n");
  }
}