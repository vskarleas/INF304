#ifndef _COMMNDES_CALCULETTE_H_

#define _COMMNDES_CALCULETTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// paquetage de gestion de commandes d'operation sur une pile d'entiers
// pour la calculette.
// Le format d'un fichier est le suivant :
//   une commande par ligne
//   chaque ligne contient :
//     soit une valeur entiere
//     soit un des caracteres suivants :
//       'd' : pour supprimer la valeur au sommet de la pile
//       'r' : pour effacer le contenu de la pile de la calculette
//       '+' : pour effectuer une addition
//       '-' : pour effectuer une soustraction
//       '*' : pour effectuer une multiplication
//       '/' : pour effectuer une division
//
//       une valeur entiere correspond a une commande de nature EMPILER_VALEUR
//       'd' correspond a une commande de nature DEPILER_SOMMET
//       'r' correspond a une commande de nature VIDER_PILE
//       '+' correspond a une commande de nature EFFECTUER_ADDITION
//       '-' correspond a une commande de nature EFFECTUER_SOUSTRACTION
//       '*' correspond a une commande de nature EFFECTUER_MULTIPLICATION
//       '/' correspond a une commande de nature EFFECTUER_DIVISION
// Si un fichier ne respecte pas ce format,
// la valeur COMMANDE_INCORRECTE est retournee

// partie specification

typedef enum {
  VIDER_PILE,
  DEPILER_SOMMET,
  EMPILER_VALEUR,
  EFFECTUER_ADDITION,
  EFFECTUER_SOUSTRACTION,
  EFFECTUER_MULTIPLICATION,
  EFFECTUER_DIVISION,
  COMMANDE_INCORRECTE
} nature_commande;

typedef struct {
  nature_commande cmd;
  int arg; // valeur dans le cas cmd = EMPILER_VALEUR
} commande;

// le fichier dont le nom est donne en parametre est ouvert en lecture
// la prochaine commande est prete a etre lue.
FILE *ouvrir_commandes(char *nom_fichier);

// renvoie vrai si la fin du fichier de commandes est atteinte.
int fin_commandes(FILE *fichier);

// renvoie la commande correspondant a la chaine de caracteres str
commande commande_texte(char str[]);

// lit et renvoie la prochaine commande du fichier
commande commande_suivante(FILE *fichier);

// le fichier de commande n'est plus accessible
// en lecture.
void fermer_commandes(FILE *fichier);

// affiche la commande
void print_commandes(commande command);

#endif
