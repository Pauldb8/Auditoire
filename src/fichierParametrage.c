/*
 * fichierParametrage.c
 *
 *  Created on: 10 mai 2013
 *      Author: Pauldb
 */

#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR 51

/*Permet de créer 1 anneeSection */
T_AnneeSection demanderInfo(T_AnneeSection anneeSection)
{
    system("cls");
    printf("**** Creation d'annee/section **** \n\n");

    int i = 0, j = 0, k = 0;

        printf("Nom (ex : 1TI) : ");
        fflush(stdin);
        gets(anneeSection.nomAnneeSection);
        printf("Nombre de Classes : ");
        fflush(stdin);
        scanf("%d", &anneeSection.nbClasses);

        anneeSection.tabClasse = (T_Classe *)malloc(anneeSection.nbClasses * sizeof(T_Classe));
        if(anneeSection.tabClasse == NULL)
            exit(0);

        anneeSection.nomClasse = (char **)malloc(anneeSection.nbClasses * sizeof(char*));
        if(anneeSection.nomClasse == NULL)
            exit(0);

        for(i = 0 ; i < anneeSection.nbClasses ; i++)
        {
            anneeSection.nomClasse[i] = (char *)malloc(MAX_CHAR * sizeof(char));
            if(anneeSection.nomClasse[i] == NULL)
                exit(0);
            printf("\t Nom de la classe %d (ex : 1TM1) : ", i+1);
            fflush(stdin);
            gets(anneeSection.nomClasse[i]);
        }

        printf("\n");

        printf("Nombre de cours par etudiant : ");
        scanf("%d", &anneeSection.nbCoursParEtudiant);

        anneeSection.tabCours = malloc(anneeSection.nbCoursParEtudiant * sizeof(T_Cours));
        if(anneeSection.tabCours == NULL)
            exit(0);

        for(i = 0 ; i < anneeSection.nbCoursParEtudiant ; i++)
        {
            printf("\t Nom du cours %d : ", i+1);
            fflush(stdin);
            gets(anneeSection.tabCours[i].nomCours);
            printf("\t Ponderation de ce cours : ");
            fflush(stdin);
            scanf("%d", &anneeSection.tabCours[i].ponderation);
        }

        printf("\n");

    return anneeSection;

    free(anneeSection.tabClasse);
    free(anneeSection.nomClasse);
    free(anneeSection.tabCours);

    for(i = 0 ; i < anneeSection.nbClasses ; i++)
        free(anneeSection.nomClasse[i]);

}

