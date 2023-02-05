#include "commandes_pile.h"

FILE *ouvrir_commandes(char *nom_fichier) { return fopen(nom_fichier, "r"); }

int fin_commandes(FILE *fichier) {
  if (fichier == NULL)
    return 1;
  return feof(fichier);
}

commande commande_texte(char str[]) { //on pourrait aussi l'ecrire comme *str
  int lgt;
  char c;
  commande command;

  lgt = strlen(str); //initialise le fin avec /0
  if (str[lgt - 1] == '\n') {
    str[lgt - 1] = '\0';
    lgt--;
  }

  if (lgt == 0)
    command.cmd = COMMANDE_INCORRECTE;

  if (lgt > 10) //il n'accepte pas des fichiers plus grandes que d'indice 10 pour les donnes
    command.cmd = COMMANDE_INCORRECTE;

  c = str[0]; //-- identifier la commande str
  switch (c) { //here a beautiful switch!
  case 'p': //afficher
    if (strlen(str) > 1) {
      command.cmd = COMMANDE_INCORRECTE;
    }
    command.cmd = AFFICHER_PILE;
    break;
  case 's': //sommet
    if (strlen(str) > 1) {
      command.cmd = COMMANDE_INCORRECTE;
    }
    command.cmd = AFFICHER_SOMMET;
    break;
  case 'd': 
    if (strlen(str) > 1) {
      command.cmd = COMMANDE_INCORRECTE;
    }
    command.cmd = DEPILER_SOMMET;
    break;
  case 'v': //vide
    if (strlen(str) > 1) {
      command.cmd = COMMANDE_INCORRECTE;
    }
    command.cmd = AFFICHER_PILE_VIDE;
    break;
  case 't': //taille
    if (strlen(str) > 1) {
      command.cmd = COMMANDE_INCORRECTE;
    }
    command.cmd = AFFICHER_TAILLE_PILE;
    break;
  case 'r':
    if (strlen(str) > 1) {
      command.cmd = COMMANDE_INCORRECTE;
    }
    command.cmd = VIDER_PILE;
    break;
  default:                   // -- recuperer la valeur correspondant a t
    command.arg = atoi(str); //-- valeur entiere correcte
    command.cmd = EMPILER_VALEUR;
    break;
  }
  return command;
}

commande commande_suivante(FILE *fichier) {
  int lgt = 1000; // 11;
  char str[lgt];

  memset(str, 0, lgt);
  if (fgets(str, lgt, fichier) != NULL) {
    // lire une sequence d'espaces : notamment les lignes vides
    fscanf(fichier, " ");
    return commande_texte(str);
  }
  return (commande){COMMANDE_INCORRECTE, 0};
}

void fermer_commandes(FILE *fichier) {
  if (fichier != NULL)
    fclose(fichier);
}

void print_commandes(commande command) {
  switch (command.cmd) {
  case VIDER_PILE:
    printf("VIDER_PILE\n");
    break;
  case DEPILER_SOMMET:
    printf("DEPILER_SOMMET\n");
    break;
  case EMPILER_VALEUR:
    printf("EMPILER_VALEUR : %d \n", command.arg);
    break;
  case AFFICHER_PILE:
    printf("AFFICHER_PILE\n");
    break;
  case AFFICHER_SOMMET:
    printf("AFFICHER_SOMMET \n");
    break;
  case AFFICHER_PILE_VIDE:
    printf("AFFICHER_PILE_VIDE \n");
    break;
  case AFFICHER_TAILLE_PILE:
    printf("AFFICHER_TAILLE_PILE \n");
    break;
  case COMMANDE_INCORRECTE:
    printf("COMMANDE_INCORRECTE \n");
    break;
  }
}
