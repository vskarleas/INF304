#include "es_tableau.h"
#include <stdio.h>

void lire_tableau(char *nomFichier, tableau_entiers *t) {
  /* Descripteur du fichier d'entree */
  FILE *fichier;
  int i;

  /* Ouverture du fichier en lecture */
  fichier = fopen(nomFichier, "r");

  /* Lecture de la taille du tableau */
  fscanf(fichier, "%d", &(t->taille));

  /* Lecture des valeurs du tableau */
  for (i = 0; i < t->taille; i++) {
    fscanf(fichier, "%d", &(t->tab[i]));
  }
  fclose(fichier);
}

void ecrire_tableau(char *nomFichier, tableau_entiers *t) {
  /* Descripteur du fichier de sortie */
  FILE *fichier;
  int i;

  /* Creer et ouvrir le fichier en ecriture */
  fichier = fopen(nomFichier, "w");

  /* ecrire la taille du tableau dans le fichier */
  fprintf(fichier, "%d\n", t->taille);

  /* ecrire les valeurs du tableau */
  for (i = 0; i < t->taille; i++) {
    fprintf(fichier, "%d\n", t->tab[i]);
  }
  /* Fermeture du fichier */
  fclose(fichier);
}
