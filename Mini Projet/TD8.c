#include <stdio.h>
#include <stdlib.h>

int alea_borne(int borne_inf, int borne_sup)
{
    return (rand() % (borne_sup - borne_inf + 1)) + borne_inf;
}

int alea_piece()
{
    return alea_borne(0, 1);
}

int alea_de()
{
    return alea_borne(1, 6);
}

void tirages_alea_borne(int nb_tirages, int borne_inf, int borne_sup, int* valeurs)
{
    printf("****************************\nTirages borne\n");
    for (int i = 0; i < nb_tirages; i++)
    {
        valeurs[i] = alea_borne(borne_inf, borne_sup);
        printf("\t%d\n", valeurs[i]);
    }
    printf("****************************\n");
}

void tirages_alea_piece(int nb_tirages, int *valeurs)
{
    printf("****************************\nTirages pieces\n");
    for (int i = 0; i < nb_tirages; i++)
    {
        valeurs[i] = alea_piece();
        if (valeurs[i] == 0)
        {
            printf("\tPile\n");
        }
        else
        {
            printf("\tFace\n");
        }
    }
    printf("****************************\n");
}

void tirages_alea_des(int nb_tirages, int *valeurs)
{
    printf("****************************\nTirages dés\n");
    for (int i = 0; i < nb_tirages; i++)
    {
        valeurs[i] = alea_de();
        printf("\t%d\n", valeurs[i]);
    }
    printf("****************************\n");
}

int main()
{
    int tirages_borne[100];
    tirages_alea_borne(100, 0, 50, tirages_borne);
    int tirages_piece[100];
    tirages_alea_piece(100, tirages_piece);
    int N;
    scanf("%d", &N);
    int tirages_de[100000];
    tirages_alea_des(N, tirages_de);
    FILE *f = fopen("tirages_des", "w");
    fprintf(f,"%d\n\n",N);
    for (int i = 0; i < N; i++)
    {
        fprintf(f,"%d\n", tirages_de[i]);
    }
    fclose(f);
}