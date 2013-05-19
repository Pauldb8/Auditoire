/*
 * creerSection.c
 *
 *  Created on: 13 mai 2013
 *      Author: Paul
 */

#include "structures.h"
#include "tools.h"
#include "sauvegardeFichier.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>

T_Section creerSection(char * URL)
{
    T_Section aRenvoyer;
    int i, j, k;

    effacerEcran();
    printf("*** Creation d'une nouvelle section *** \n\n");

    printf("Nom de la section : ");
    fflush(stdin);
    gets(aRenvoyer.nom);
    printf("\n");
    printf("Nombre d'annee de la section : ");
    fflush(stdin);
    scanf("%d", &aRenvoyer.nbrAnnees);

    aRenvoyer.tabAnnees = malloc(aRenvoyer.nbrAnnees * sizeof(T_Annee));

    for(i = 0 ; i < aRenvoyer.nbrAnnees ; i++)
    {
        printf("\n");
        printf("\t.Nom de l'annee %d (ex : 1TI) : ", i+1);
        fflush(stdin);
        gets(aRenvoyer.tabAnnees[i].nomAnneeSection);
        printf("\t\tNombre de classes de cette annees (%s) : ", aRenvoyer.tabAnnees[i].nomAnneeSection);
        fflush(stdin);
        scanf("%d", &aRenvoyer.tabAnnees[i].nbClasses);

        aRenvoyer.tabAnnees[i].tabClasse = malloc(aRenvoyer.tabAnnees[i].nbClasses * sizeof(T_Classe));
        aRenvoyer.tabAnnees[i].nomClasse = (char **) malloc(aRenvoyer.tabAnnees[i].nbClasses * sizeof(char*));

        for(j = 0 ; j < aRenvoyer.tabAnnees[i].nbClasses ; j++)
        {
            aRenvoyer.tabAnnees[i].nomClasse[j] = (char *)malloc(MAX_CHAR * sizeof(char));
            printf("\t\t\t-Nom de la classe %d : ", i+1);
            fflush(stdin);
            gets(aRenvoyer.tabAnnees[i].nomClasse[j]);
        }

        printf("\n");
        printf("\t\tNombre de cours par etudiant : ");
        scanf("%d", &aRenvoyer.tabAnnees[i].nbCoursParEtudiant);

        aRenvoyer.tabAnnees[i].tabCours = malloc(aRenvoyer.tabAnnees[i].nbCoursParEtudiant * sizeof(T_Cours));

        for(k = 0 ; k < aRenvoyer.tabAnnees[i].nbCoursParEtudiant ; k++)
        {
            printf("\t\t\t Nom du cours %d : ", i+1);
            fflush(stdin);
            gets(aRenvoyer.tabAnnees[i].tabCours[k].nomCours);
            printf("\t\t\t Ponderation de ce cours : ");
            fflush(stdin);
            scanf("%d", &aRenvoyer.tabAnnees[i].tabCours[k].ponderation);
        }


    }

    sauverFichierParametrage(aRenvoyer);
    printf("\nLa section est correctement creer, et correctement enregistree ! \n\n");
    system("Pause");
    return aRenvoyer;

    free(aRenvoyer.tabAnnees);

    for(i = 0 ; i < aRenvoyer.nbrAnnees ; i++)
    {
        free(aRenvoyer.tabAnnees[i].tabClasse);
        free(aRenvoyer.tabAnnees[i].nomClasse);
        free(aRenvoyer.tabAnnees[i].tabCours);

        for(k = 0 ; k < aRenvoyer.tabAnnees[i].nbClasses ; k++)
            free(aRenvoyer.tabAnnees[i].nomClasse[k]);
    }
}

