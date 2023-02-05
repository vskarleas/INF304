#include "type_pile_erreurs_2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

/* Constructeurs */

/* Créer une pile vide
   Précondition : p != NULL
   Résultat : p est une pile vide
   Retourne :
     - OK si la fonction s'est déroulée correctement
     - POINTEUR_NUL si p == NULL
 */
erreur_pile creer_pile(PileEntiers *p)
{
  if (p == NULL)
  {
    return POINTEUR_NUL;
  }
  p->n = 0;
  return OK;
}

/* Opérations d'accès */

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers *p)
{
  return (p->n == 0);
}

/* Renvoie l'entier en haut de la pile
   Précondition : p non vide
   Résultat : res contient l'entier en haut de la pile
   Retourne :
     - OK si la précondition est valide
     - PILE_VIDE si p est vide. Dans ce cas, la valeur de res n'est
       pas définie
 */
erreur_pile sommet(PileEntiers *p, int *res)
{
  for (int i = 0; i < p->n; i++)
  {
    printf("| %d ", p->tab[i]);
  }
  printf("|\n");
  if (est_vide(p))
  {
    return PILE_VIDE;
  }
  *res = p->tab[0];
  for (int i = 0; i < p->n; i++)
  {
    printf("| %d ", p->tab[i]);
  }
  printf("|\n");
  return OK;
}

/* Renvoie le nombre d'éléments dans la pile */
int taille(PileEntiers *p)
{
  return p->n;
}

/* Afficher les éléments de la pile */
void print(PileEntiers *p)
{
  for (int i = 0; i < p->n; i++)
  {
    printf("| %d ", p->tab[i]);
  }
  printf("|\n");
}

/* Opérations de modification */

/* Vider la pile p
   Précondition : p != NULL
   Résultat : p est une pile vide
   Retourne :
     - OK si la fonction s'est déroulée correctement
     - POINTEUR_NUL si p == NULL
*/
erreur_pile vider(PileEntiers *p)
{
  if (p == NULL)
  {
    return POINTEUR_NUL;
  }
  p->n = 0;
  return OK;
}

void vider_protege(PileEntiers *p)
{
  if (vider(p) == POINTEUR_NUL)
  {
  printf("La pile n'a pas pu etre videe car elle est invalide.\n");
  }
}

/* Empiler un entier x
   Précondition : p != NULL et taille(p) < TAILLE_MAX
   Résultat : l'entier x est placé en haut de la pile
   Retourne :
     - OK si la fonction s'est déroulée correctement
     - POINTEUR_NUL si p == NULL
     - PILE_PLEINE si la structure est pleine, et l'entier ne peut
       être empilé. Dans ce cas la pile p n'est pas modifiée
*/
erreur_pile empiler(PileEntiers *p, int x)
{
  if (p == NULL)
  {
    return POINTEUR_NUL;
  }

  if (p->n == TAILLE_MAX)
  {
    return PILE_PLEINE;
  }

  p->tab[p->n] = x;
  p->n++;
  return OK;
}

void empiler_protege(PileEntiers *p, int x)
{

  erreur_pile retour = empiler(p, x);
  if (retour == POINTEUR_NUL)
  {
    printf("La pile n'a pas pu etre empilee car elle est invalide.\n");
  }
  else
  {
    if (retour == PILE_PLEINE)
    {
      printf("La pile est pleine donc on ne peut pas empiler.\n");
    }
  }
}

/* Supprimer et renvoyer l'entier en haut de la pile
   Précondition : p != NULL et p non vide
   Résultat :
     - l'entier en haut de la pile est enlevé de la pile
     - l'entier resultat contient l'entier dépilé
   Retourne :
     - OK si la précondition est valide
     - POINTEUR_NUL si p == NULL
     - PILE_VIDE si p est vide. Dans ce cas, la pile n'est pas
       modifiée
*/
erreur_pile depiler(PileEntiers *p, int *resultat)
{
  if (p == NULL)
  {
    return POINTEUR_NUL;
  }

  if (est_vide(p))
  {
    return PILE_VIDE;
  }

  p->n--;
  *resultat = p->tab[p->n];
  return OK;
}

int depiler_protege(PileEntiers *p)
{

  int valeur;
  erreur_pile retour = depiler(p, &valeur);
  if (retour == POINTEUR_NUL)
  {
    printf("La pile n'a pas pu etre depilee car elle est invalide.\n");
  }
  else
  {
    if (retour == PILE_VIDE)
    {
      printf("La pile est vide donc on ne peut pas depiler.\n");
    }
  }
  return valeur;
}

int verification_operations(PileEntiers *p)
{
  if (p->n < 2)
  {
    printf("Il faut au moins deux éléments pour effectuer cette opération.\n");
    return FALSE;
  }
  return TRUE;
}