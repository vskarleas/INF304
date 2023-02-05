#include "type_pile.h"
#include <stdio.h>

void creer_pile(PileEntiers *p) {
    p->n=0;
}

int est_vide(PileEntiers *p) {
    return p->n == 0;
    
}

int sommet(PileEntiers *p) {
    return p->tab[(p->n-1)];
}

int taille(PileEntiers *p) {
    return p->n;
}

void print(PileEntiers *p) {
    printf("| ");
    for (int i=0; i<(p->n); i++) {
        printf("%d | ", p->tab[i]);
    }
    printf("\n");
}

void vider(PileEntiers *p){
    p->n = 0;
}

void empiler(PileEntiers *p, int x) {
    p->tab[p->n]= x;
    p->n++;
}

int depiler(PileEntiers *p) {
    int x = p->tab[p->n-1];
    p->n--;
    return x;
}