#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
/*
 *  Exercice 1:
 *      Le programme est accepté par l'automate correspondant a ((E\A)*MA(E\A))*
 *
 *  Exercice 2:
 *      - correct accepté : { 1 M { G } { A } ? C ! } C !
 *      - incorrect rejeté : { A C ! } C !
 *      - correct rejeté : { 1 M  G D { G } { A } ? C ! } C !
 *      - incorrect accepté : { 1 M A C! } C !
 *
 * Exercice 3:
 *  
 */

#define VIENT_DEFAULT 0
#define VIENT_DE_TOURNER_A_GAUCHE 1
#define VIENT_DE_TOURNER_A_DROITE 2

#define TESTER_MA false
#define TESTER_GD true

/*
 *      - correct accepté : { 1 M { G } { A } ? C ! } C !
 *      - incorrect rejeté : { A C ! } C !
 *      - correct rejeté : { 1 M  G D { G } { A } ? C ! } C !
 *      - incorrect accepté : { 1 M A C! } C !
*/
void observateur_MA(bool *M_juste_avant, char commande_actuelle)
{
    #if TESTER_MA
    switch (commande_actuelle){
        case 'M' :
            *M_juste_avant = true;
            break;
        case 'A' :
            if (!*M_juste_avant){
                fprintf(stderr, "La mesure n'a pas était faite (la propriete 1 n'est pas valide).\n");
                exit(1);
            }
            else
            {
                *M_juste_avant = false;
            }
            break;
        default:
            *M_juste_avant = false;
            return;
            break;
        }
    #endif
}

/*
 *      - correct accepté : { 1 M { G } { A } ? C ! } C !
 *      - incorrect rejeté : { G D A C ! } C !
 *      - correct rejeté : N'existe pas
 *      - incorrect accepté : { D 7 M G A C ! } C !
 */
void observateur_GD(int *etat, char commande_actuelle)
{
    #if TESTER_GD
    switch (commande_actuelle)
    {
    case 'G':
        if (*etat == VIENT_DE_TOURNER_A_DROITE)
        {
            fprintf(stderr, "Le robot a tourné pour rien (la propriete 2 n'est pas valide).\n");
            exit(1);
        }
        else
        {
            *etat = VIENT_DE_TOURNER_A_GAUCHE;
        }
        break;
    case 'D':
        if (*etat == VIENT_DE_TOURNER_A_GAUCHE)
        {
            fprintf(stderr, "Le robot a tourné pour rien (la propriete 2 n'est pas valide).\n");
            exit(1);
        }
        else
        {
            *etat = VIENT_DE_TOURNER_A_DROITE;
        }
        break;
    default:
        *etat = VIENT_DEFAULT;
        break;
    }
    #endif
}