#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Case conversion_char_case(char c)
{
  switch (c)
  {
  case '#':
    return ROCHER;
  case '.':
    return LIBRE;
  case '~':
    return EAU;
  case 'C':
    return LIBRE;
  default:
    return LIBRE;
  }
}

char conversion_case_char(Case c)
{
  switch (c)
  {
  case LIBRE:
    return '.';
  case ROCHER:
    return '#';
  case EAU:
    return '~';
  default:
    return 'X';
  }
}

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y)
{
  int l, h;   // Dimensions du terrain
  int rx, ry; // Coordonnées initiales du robot
  bool robot_trouve = false;

  if (f == NULL)
  {
    return ERREUR_FICHIER;
  }

  // Lecture de la largeur
  fscanf(f, "%d\n", &l);
  if (l <= 0 || l >= DIM_MAX)
  {
    return ERREUR_LARGEUR_INCORRECTE;
  }
  t->largeur = l;

  // Lecture de la hauteur
  fscanf(f, "%d\n", &h);
  if (h <= 0 || h >= DIM_MAX)
  {
    return ERREUR_HAUTEUR_INCORRECTE;
  }
  t->hauteur = h;

  // Lecture du terrain
  char lettre;
  int j;
  for (j = 0; !feof(f); j++)
  {
    if (j >= h)
    {
      return ERREUR_FORMAT;
    }
    fscanf(f, "%c", &lettre);
    int i;
    for (i = 0; !feof(f) && lettre != '\n'; i++)
    {
      if (i >= l)
      {
        return ERREUR_LIGNE_TROP_LONGUE;
      }
      if (lettre == 'C')
      {
        robot_trouve = true;
        rx = i;
        ry = j;
      }

      t->tab[i][j] = conversion_char_case(lettre);
      fscanf(f, "%c", &lettre);
    }
    if (i < l)
    {
      return ERREUR_LIGNE_TROP_COURTE;
    }

  }
  if (j < h - 1)
  {
    return ERREUR_LIGNES_MANQUANTES;
  }

  // Initialisation de la position du robot
  if (!robot_trouve)
  {
    return ERREUR_POSITION_ROBOT_MANQUANTE;
  }
  *x = rx;
  *y = ry;

  return OK;
}

/* Largeur d'un terrain */
int largeur(Terrain *t)
{
  return t->largeur;
}

/* Hauteur d'un terrain */
int hauteur(Terrain *t)
{
  return t->hauteur;
}

/* Indique si la case de coordonnées (x,y) est libre
   Renvoie vrai ssi les 3 conditions suivantes sont vraies :
    - 0 <= x < largeur
    - 0 <= y < hauteur
    - t.tab[x][y] = LIBRE
 */
int est_case_libre(Terrain *t, int x, int y)
{
  return t->tab[x][y] == LIBRE && x < t->largeur && y < t->hauteur;
}

/* Affichage d'un terrain t sur la sortie standard */
void afficher_terrain(Terrain *t)
{
  for (int j = 0; j < t->hauteur; j++)
  {
    for (int i = 0; i < t->largeur; i++)
    {
      printf("%c", conversion_case_char(t->tab[i][j]));
    }
    printf("\n");
  }
}

/* Écriture d'un terrain t dans un fichier f ouvert en écriture.
   x et y contiennent les coordonnées du robot
   Le terrain est écrit au format lisible par lire_terrain */
void ecrire_terrain(FILE *f, Terrain *t, int x, int y)
{
  for (int j = 0; j < t->hauteur; j++)
  {
    for (int i = 0; i < t->largeur; i++)
    {
      if (i==x && j==y)
      {
        fprintf(f, "C");
      }
      else
      {
        fprintf(f, "%c", conversion_case_char(t->tab[i][j]));
      }
    }
    fprintf(f,"\n");
  }
}

bool est_case_au_bord(Terrain *t, int x, int y)
{
  return x == 0 || x == t->largeur || y == 0 || y == t->hauteur;
}

bool est_case_accessible(Terrain *t, int x, int y, Position *deja_vu, int longueur_deja_vu)
{
  Position p;
  p.x = x; p.y = y;
  deja_vu[longueur_deja_vu] = p;
  longueur_deja_vu++;
  if (t->tab[x][y]!=LIBRE)
  {
    return false;
  }
  if (est_case_au_bord(t, x, y))
  {
    return true;
  }
  else
  {
    bool est_case_Nord_deja_vue = false;
    bool est_case_Sud_deja_vue = false;
    bool est_case_Est_deja_vue = false;
    bool est_case_Ouest_deja_vue = false;
    for (int i = 0; i < longueur_deja_vu; i++)
    {
      if (deja_vu[i].x == x && deja_vu[i].y == y - 1){
        est_case_Nord_deja_vue = true;
      }
      if (deja_vu[i].x == x && deja_vu[i].y == y + 1)
      {
        est_case_Sud_deja_vue = true;
      }
      if (deja_vu[i].x == x + 1 && deja_vu[i].y == y){
        est_case_Est_deja_vue = true;
      }
      if (deja_vu[i].x == x - 1 && deja_vu[i].y == y)
      {
        est_case_Ouest_deja_vue = true;
      }
    }
    return (!est_case_Nord_deja_vue && est_case_accessible(t, x, y - 1, deja_vu, longueur_deja_vu)) || (!est_case_Sud_deja_vue && est_case_accessible(t, x, y + 1, deja_vu, longueur_deja_vu)) || (!est_case_Est_deja_vue && est_case_accessible(t, x + 1, y, deja_vu, longueur_deja_vu)) || (!est_case_Ouest_deja_vue && est_case_accessible(t, x - 1, y, deja_vu, longueur_deja_vu));
  }
}

bool est_terrain_valide(Terrain *t, int x, int y)
{
  Position pos[100000];
  return est_case_accessible(t, x, y, pos, 0);
}

void init_terrain(Terrain *t)
{
  t->hauteur = 0;
  t->largeur = 0;
  for (int i = 0; i < DIM_MAX; i++)
  {
    for (int j = 0; j < DIM_MAX;j++)
    {
      t->tab[i][j] = LIBRE;
    }
  }
}

float densite(Terrain *t)
{
  int nb_obstacles = 0;
  for (int i = 0; i < t->largeur; i++)
  {
    for (int j = 0; j < t->hauteur; j++)
    {
      if (!(t->tab[i][j] == LIBRE))
      {
        nb_obstacles++;
      }
    }
  }
  float densite = nb_obstacles / (float)(t->largeur * t->hauteur);
  return densite;
}