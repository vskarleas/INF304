#include "commandes_pile.h"
#include <stdio.h>
#include "type_pile_erreurs_2.h"

int main(int argc, char **argv) {
  FILE *fichier = NULL;
  if (argc != 2) {
    printf("mauvaise utilisation : donnez un nom de fichier en argument\n");
    return 0;
  }

  fichier = ouvrir_commandes(argv[1]);
  PileEntiers p;
  if (creer_pile(&p) == POINTEUR_NUL) {
    printf("The pointer is null and we can't proceed\n");
  }
  else if (creer_pile(&p) == OK) {
  commande command;

  int resultat;

  while (!fin_commandes(fichier)) {
    command = commande_suivante(fichier);
    print_commandes(command);

    
    switch (command.cmd) {
    case VIDER_PILE:
      if (vider(&p) == OK){
        break;
      }
      else if (vider(&p) == POINTEUR_NUL) {
        printf("Le pointeur de pile est null");
        break;
      }
      else {
        printf("Unknow error - section trying to vide the Pile");
        break;
      }
    case DEPILER_SOMMET:
      if (depiler(&p, &resultat)== PILE_VIDE){
        printf("Le pile est vide");
        break;
      } 
      else if (depiler(&p, &resultat)== POINTEUR_NUL){
        printf("Le pointeur de pile est null - section depiling valeur");
        break;
      }
      else {
        printf("Unknown error at Depiling Sommet\n");
        break;
      }
    case EMPILER_VALEUR:
      if (empiler(&p, command.arg) == OK){
        break;
      }
      else if (empiler(&p, command.arg) == PILE_PLEINE){
        printf("Le pile est plus grand que la taille max - section empiller valeur");
        break;
      }
      else {
        printf("Le pointeur de pile est null  - section empiller valeur");
        break;
      }
    case AFFICHER_PILE:
      print(&p);
      break;
    case AFFICHER_SOMMET:
      if (sommet(&p, &resultat)==OK) {
        printf("Sommet de la pile : %d \n", resultat);
        break;
      }
      else {
        printf("Le pile etait vide"); //message d'erreur
        break;
      }
    case AFFICHER_PILE_VIDE:
      if (est_vide(&p) == 1) {
        printf("La pile est vide\n");
      } else {
        printf("La pile n'est pas vide\n");
      }
      break;
    case AFFICHER_TAILLE_PILE:
      printf("Taille de la pile : %d \n", taille(&p));
      break;
    case COMMANDE_INCORRECTE:
      printf("Commande incorrecte !\n");
      break;
    }
    print(&p);
    printf("\n");
  }
  fermer_commandes(fichier);
  }
  else {
    printf("Unknow error - section pointeur of Pile");
  }
  return 0;
}
