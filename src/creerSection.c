/*
 * creerSection.c
 *
 *  Created on: 13 mai 2013
 *      Author: Paul
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "tools.h"
#include "sauvegardeFichier.h"
#include "defines.h"
#include "fichierParametrage.h"

T_Section creerSection(char * URL)
{
    T_Section aRenvoyer;
    int i, j, k;
    char abbr[2];
    char abbrAnnee[2];

    effacerEcran();
    printf("*** Creation d'une nouvelle section *** \n\n");

    printf("Nom de la section : ");
    scanf("%s", aRenvoyer.nom);
    printf("Abbreviation de la section (TI, HE...) : ");
    do{
    	scanf("%s", abbr);
    	if(strlen(abbr) > 2)
    		printf("Doit faire maximum 2 caractères : ");
    }while(strlen(abbr) > 2);
    strcpy(aRenvoyer.abbreviation, abbr);

    printf("Nombre d'annee de la section : ");
    scanf("%d", &aRenvoyer.nbrAnnees);

    aRenvoyer.tabAnnees = malloc(aRenvoyer.nbrAnnees * sizeof(T_Annee));

    for(i = 0 ; i < aRenvoyer.nbrAnnees ; i++)
    {
    	aRenvoyer.tabAnnees[i] = demanderInfo(aRenvoyer.tabAnnees[i], aRenvoyer.abbreviation);
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

