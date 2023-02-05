
#define TAILLE_MAX 100

typedef struct {
  int n;
  int tab[TAILLE_MAX];
} PileEntiers;

/* Constructeurs */

/* Creer une pile vide */
void creer_pile(PileEntiers *p);

/* Operations d'acces */

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers *p);

/* Renvoie l'entier en haut de la pile */
/* p doit etre non vide */
int sommet(PileEntiers *p);

/* Renvoie le nombre d'elements dans la pile */
int taille(PileEntiers *p);

/* Afficher les elements de la pile */
void print(PileEntiers *p);

/* Operations de modification */

/* Vider la pile p */
void vider(PileEntiers *p);

/* Empiler un entier x */
/* Precondition : taille(p) < TAILLE_MAX */
void empiler(PileEntiers *p, int x);

/* Supprimer et renvoyer l'entier en haut de la pile */
/* Precondition : p non vide */
int depiler(PileEntiers *p);
