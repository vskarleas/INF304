#ifndef _TYPE_PILE_ERREURS_H_
#define _TYPE_PILE_ERREURS_H_

typedef enum {
  OK, // Pas d'erreur
  PILE_VIDE,
  PILE_PLEINE,
  POINTEUR_NUL
} erreur_pile;

#define TAILLE_MAX 100

typedef struct {
  int n;
  int tab[TAILLE_MAX];
} PileEntiers;

/* Constructeurs */

/* Creer une pile vide
   Precondition : p != NULL
   Resultat : p est une pile vide
   Retourne :
     - OK si la fonction s'est deroulee correctement
     - POINTEUR_NUL si p == NULL
 */
erreur_pile creer_pile(PileEntiers *p);

/* Operations d'acces */

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers *p);

/* Renvoie l'entier en haut de la pile
   Precondition : p non vide
   Resultat : res contient l'entier en haut de la pile
   Retourne :
     - OK si la precondition est valide
     - PILE_VIDE si p est vide. Dans ce cas, la valeur de res n'est
       pas definie
 */
erreur_pile sommet(PileEntiers *p, int *res);

/* Renvoie le nombre d'elements dans la pile */
int taille(PileEntiers *p);

/* Afficher les elements de la pile */
void print(PileEntiers *p);

/* Operations de modification */

/* Vider la pile p
   Precondition : p != NULL
   Resultat : p est une pile vide
   Retourne :
     - OK si la fonction s'est deroulee correctement
     - POINTEUR_NUL si p == NULL
*/
erreur_pile vider(PileEntiers *p);

/* Empiler un entier x
   Precondition : p != NULL et taille(p) < TAILLE_MAX
   Resultat : l'entier x est place en haut de la pile
   Retourne :
     - OK si la fonction s'est deroulee correctement
     - POINTEUR_NUL si p == NULL
     - PILE_PLEINE si la structure est pleine, et l'entier ne peut
       etre empile. Dans ce cas la pile p n'est pas modifiee
*/
erreur_pile empiler(PileEntiers *p, int x);

/* Supprimer et renvoyer l'entier en haut de la pile
   Precondition : p != NULL et p non vide
   Resultat :
     - l'entier en haut de la pile est enleve de la pile
     - l'entier resultat contient l'entier depile
   Retourne :
     - OK si la precondition est valide
     - POINTEUR_NUL si p == NULL
     - PILE_VIDE si p est vide. Dans ce cas, la pile n'est pas
       modifiee
*/
erreur_pile depiler(PileEntiers *p, int *resultat);

int depiler_protege(PileEntiers *p);

int verification_operations(PileEntiers *p);

#endif