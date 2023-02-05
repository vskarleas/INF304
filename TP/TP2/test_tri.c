#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "es_tableau.h"
#include "tri.h"

void test_tri_insertion(int argc, char **argv) { /* a completer */
    FILE *fichier;
    FILE *testing;
    char nom_fichier[300];
    char tab[500];
    tableau_entiers t;
    if (argc<2) {
        printf("On a besoin des fichiers\n");
    }
    else {
        for (int i=1; i< argc; i++) {
        fichier = fopen(argv[i], "r");
        lire_tableau(argv[i], &t);
        tri_insertion(&t);
        strcpy(nom_fichier, argv[i]);
        strcat(nom_fichier, ".out");
        ecrire_tableau(nom_fichier, &t);

        testing = fopen(nom_fichier, "r"); //commence l'oracle avec les tests
        
        if (testing == NULL ) {
            printf("No file is accessible for %s\n", argv[i]);
        }
        else {
            printf("===========\n");
            printf("File %s has been accessed\n", nom_fichier);
            int id;
            fscanf(testing, "%d", &id);
            int taille = id;
            fscanf(testing, "%d", &id);
            int premier = id;
            for (int y = 0; y<taille-1; y++) {
                fscanf(testing, "%d", &id);
                if (premier == id) {
                    premier = id;
                }
                else if (premier > id) {
                    printf("Error! The tri isn't correct for %s\n", nom_fichier);
                    printf("The error found on line %d of the file\n", taille-y);
                    premier = id;
                }
                else {
                    premier = id;
                }
            }
            printf("Tri Test completed for %s. If there are no errors, well done!\n", nom_fichier);
        }
        }
    }
}

void test_tri_insertion_alea(int argc, char **argv) { /* a completer */
    int rera = rand() % 10; //number of files files to be created
    printf("Number of files generated: %d\n", rera);
    char nom_fichier[300];
    char nom_file[300];
    char tab[500];
    FILE *fichier;
    FILE *newfile;
    FILE *testing;
    tableau_entiers t;
    //Random files generation
    for(int i=0; i<rera; i++){
        sprintf(nom_fichier,"%d%s",i,".txt");
        fichier= fopen(nom_fichier, "w");
        int creation_numbers = rand() % 30;
        fprintf(fichier, "%d\n", creation_numbers);
        int numb;
        for (int y=0; y<creation_numbers; y++){ //Random numbers creation based on a rand taille created above inside every file
            numb = rand() % 50;
            fprintf(fichier, "%d\n", numb);
        }
        printf("File: %s\n", nom_fichier);
        //performing tri functions
        newfile=fopen(nom_fichier,"r");
        lire_tableau(nom_fichier, &t);
        tri_insertion(&t);
        strcpy(nom_file, nom_fichier);
        strcat(nom_file, ".out");
        ecrire_tableau(nom_file, &t);

        testing = fopen(nom_file, "r");
        //Testing process based on the oracle
        printf("\n");
        printf("===========\n");
        printf("Test started for %s\n", nom_file);
        printf("===========\n");
        int id;
        fscanf(testing, "%d", &id);
        int taille = id;
        fscanf(testing, "%d", &id);
        int premier = id;
        for (int y = 0; y<taille-1; y++) {
            fscanf(testing, "%d", &id);
            if (premier == id) {
                premier = id;
            }
            else if (premier > id) {
                printf("Error! The tri isn't correct for %s\n", nom_fichier);
                printf("The error found on line %d of the file\n", taille-y);
                premier = id;
                }
            else {
                premier = id;
            }
        }
            printf("Tri Test completed for %s. If there are no errors, well done!\n", nom_fichier);
    }


}
