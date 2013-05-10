/*
 * operationsSurEtudiants.c
 *
 *  Created on: 10 mai 2013
 *      Author: Pauldb
 */

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "operationsSurEtudiants.h"
#include "fichierParametrage.h"
#include "sauvegardeFichier.h"

#define INCREMENTALLOC 3

void afficherMenuGlobal(T_AnneeSection * tab)
{

    int choix = 0, nbrAnneeSection = 0, i = 0;
    char choixSauver = 0;

    printf("*** Programme de gestion de classes *** \n\n");
    printf("\t 1. Charger le tableau d'annee/section.\n");
    printf("\t 2. Creer une annee/section\n\n");

    printf("Votre choix : ");
    scanf("%d", &choix);

    if(choix == 2)
    {
        printf("Nombre d'annee/section souhaitee : ");
        scanf("%d", &nbrAnneeSection);
        tab = malloc(nbrAnneeSection * sizeof(T_AnneeSection));
        if(tab == NULL)
        {
            printf("Erreur memoire");
            exit(0);
        }

        for(i = 0 ; i < nbrAnneeSection ; i++)
            tab[i] = demanderInfo(tab[i]);

        printf("Voulez vous sauvegader ce fichier de parametrage ? : ");
        fflush(stdin);
        scanf("%c", &choixSauver);

        if(choixSauver == 'o' || choixSauver == 'O')
        {
            sauverFichierParametrage(tab, nbrAnneeSection);
        }
        else if(choixSauver == 'n' || choixSauver == 'N')
        {
            system("cls");
            afficherMenuGlobal(tab);
        }

        for(i = 0; i < nbrAnneeSection ; i++)
        {
            free(tab[i].tabCours);
            free(tab[i].tabCours[i].nomCours);
        }

    }

    else if(choix == 1)
    {
        tab = malloc(nbrAnneeSection * sizeof(T_AnneeSection));
        chargerFichierParametrage(tab);
        printf("%s", tab[0].nomAnneeSection);
    }

    /*Perte de toute les donées si free. Le faire ici ?*/
    // TODO : Voir le free.
    free(tab);

}

void creerEtudiant(T_Classe * classe)
{
    printf("*** Creation d'étudiant dans une Classe *** \n\n");

    T_Etudiant etu;

    printf("Nom : ");
    fflush(stdin);
    gets(etu.nom);
    printf("Prenom : ");
    fflush(stdin);
    gets(etu.prenom);

}
