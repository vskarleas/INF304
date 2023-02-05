#include <stdio.h>
#include "type_pile_erreurs.h"

erreur_pile creer_pile(PileEntiers *p) {
    if (p == NULL){
        return POINTEUR_NUL;
    }
    else {
        p->n=0;
        return OK;
    }
}

int est_vide(PileEntiers *p){
    if (p->n == 0){
       return 1; //est vide validee
    }
    else {
        return 0;
    }
}

erreur_pile sommet(PileEntiers *p, int *res){
    if (est_vide(p)!=1) {
        *res = p->tab[(p->n-1)]; //on veut le mettre dans le valeur du pointeur
        return OK;
    }
    else {
        return PILE_VIDE;
    }
}

int taille(PileEntiers *p){
    return p->n;
}

void print(PileEntiers *p){
    printf("| ");
    for (int i=0; i<(p->n); i++) {
        printf("%d | ", p->tab[i]);
    }
    printf("\n");
}

erreur_pile vider(PileEntiers *p) {
    if (p != NULL){
        p->n = 0;
        return OK;
    }
    else {
        return POINTEUR_NUL;
    }
}

erreur_pile empiler(PileEntiers *p, int x){
    if (p != NULL) {
        if (taille(p) < TAILLE_MAX) {
            p->tab[p->n]= x;
            p->n++;
            return OK;
        }
        else {
            return PILE_PLEINE;
        }
    }
    else {
        return POINTEUR_NUL;
    }
}

erreur_pile depiler(PileEntiers *p, int *resultat) {
    if (p != NULL){
        if (est_vide(p)!=1){
            int x = p->tab[p->n-1];
            p->n--;
            *resultat = x;
            return OK;
        }
        else {
            return PILE_VIDE;
        }
    }
    else {
        return POINTEUR_NUL;
    }
}