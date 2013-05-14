/*
 * creerSection.c
 *
 *  Created on: 13 mai 2013
 *      Author: Paul
 */

#include "structures.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

T_Section creerSection(char * URL)
{
    T_Section aRenvoyer;

    effacerEcran();
    printf("*** Creation d'une nouvelle section *** \n\n");

    printf("Nom de la section : ");
    fflush(stdin);
    gets(aRenvoyer.nom);
    printf("Nombre d'annee de la section : ");
    scanf("%d", &aRenvoyer.nbrAnnees);

    // Création d'uine classe vide.
    T_Annee *tabAnnees;
    aRenvoyer.tabAnnees = tabAnnees;

    printf("TODO");
    system("PAUSE");
    return aRenvoyer;
}

