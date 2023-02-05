#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
/*
 *  Exercice 1:
 *      Le programme est accepté par l'automate correspondant a ((E\A)*MA(E\A))*
 *
 *  Exercice 2:
 *      - { 1 M { G } { A } ? C ! } C !
 *      - { A C ! } C !
 *      - { 1 M  G D { G } { A } ? C ! } C !
 *      - { 1 M A C! } C !
 *
 * Exercice 3:
 *  
 */

void observateur_MA(bool *M_juste_avant, char commande_actuelle);

void observateur_GD(int *etat, char commande_actuelle);