#include "type_pile_erreurs_2.h"
#include "commandes_calculette.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *fichier = NULL;

    // test nombre d'arguments
    if (argc != 2)
    {
        printf("mauvaise utilisation : donnez un nom de fichier en argument\n");
        exit(EXIT_FAILURE);
    }

    // creation d'une pile
    PileEntiers *p = malloc(sizeof(PileEntiers));
    creer_pile(p);

    fichier = ouvrir_commandes(argv[1]);

    commande command;

    int x, y;

    while (!fin_commandes(fichier))
    {
        command = commande_suivante(fichier);
        print_commandes(command);
        switch (command.cmd)
        {
        case VIDER_PILE:
            vider_protege(p);
            break;
        case DEPILER_SOMMET:
            depiler_protege(p);
            break;
        case EMPILER_VALEUR:
            empiler_protege(p, command.arg);
            break;
        case EFFECTUER_ADDITION:
            if (verification_operations(p))
            {
                x = depiler_protege(p);
                y = depiler_protege(p);
                empiler(p, y + x);
            }
            break;
        case EFFECTUER_SOUSTRACTION:
            if (verification_operations(p))
            {
                x = depiler_protege(p);
                y = depiler_protege(p);
                empiler(p, y - x);
            }
            break;
        case EFFECTUER_MULTIPLICATION:
            if (verification_operations(p))
            {
                x = depiler_protege(p);
                y = depiler_protege(p);
                empiler(p, y * x);
            }
            break;
        case EFFECTUER_DIVISION:
            if (verification_operations(p))
            {
                x = depiler_protege(p);
                y = depiler_protege(p);
                empiler(p, y / x);
            }
            break;
        case COMMANDE_INCORRECTE:
            printf("Commande incorrecte !\n");
            break;
        }
        print(p);
    }

    fermer_commandes(fichier);

    free(p);
    return 0;
}