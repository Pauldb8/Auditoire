
/*
 * operationsChoix.c
 *
 *  Created on: 11 mai 2013
 *      Author: Pauldb
 */

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"
#include "fichierParametrage.h"
#include "sauvegardeFichier.h"
#include "operationsEtudiants.h"
#include "tools.h"


void afficherMenuChoixClasse(T_Section sct, int choix)
{
    system("cls");
    int i, choixAnnee;

    effacerEcran();

    printf("Sur quelle classe de la section %s voulez vous travailler ?\n\n", sct.nom);
    for(i = 0 ; i < sct.tabAnnees[choix].nbClasses ; i++)
        printf("\t%d. %s\n", i+1, sct.tabAnnees[choix].nomClasse[i]);

    printf("\nVotre choix : ");
    scanf("%d", &choixAnnee);
    administrationClasse(&sct.tabAnnees[choix].tabClasse[choixAnnee-1], sct.nom);
}

void afficherMenuChoixAnnee(T_Section * tab)
{
    int i, choix;

    printf("Veuillez choisir une annee a gerer : \n\n");

    for(i = 0 ; i < tab->nbrAnnees ; i++)
        printf("\t%d. %s\n", i+1, tab->tabAnnees[i].nomAnneeSection);

    printf("\nVotre choix : ");
    scanf("%d", &choix);

    /*tab[choix - 1] car on propose 1 et 2 à la place de 0 et 1, étant les positions réelles dans le tableau*/
    afficherMenuChoixClasse(*tab, choix-1);
}


void administrationAnnees(T_Section * tab)
{

    int choix = 0, nbrAnneeACreer = 0, i = 0;
    char choixSauver = 0;

    printf("*** Programme de gestion de classes *** \n\n");
    printf("\t 1. Charger le tableau d'annee de cette section (ex : 1TI) .\n");
    printf("\t 2. Creer une annee\n\n");

    printf("Votre choix : ");
    scanf("%d", &choix);


    if(choix == 2)
    {
        if(tab->nbrAnnees > 0)
        {
            printf("Il y'a deja %d annee dans la section %s\n", tab->nbrAnnees, tab->nom);
            printf("Combien d'annees souhaitez vous ajouter : ");
            scanf("%d", &nbrAnneeACreer);

           tab->tabAnnees = realloc(tab->tabAnnees, (tab->nbrAnnees + nbrAnneeACreer) * sizeof(T_Annee));
           printf("nbrAnneeACreer: %d\n", nbrAnneeACreer);

            for(i = 0 ; i < nbrAnneeACreer ; i++)
                tab->tabAnnees[tab->nbrAnnees + i] = demanderInfo(tab->tabAnnees[tab->nbrAnnees + i]);

            printf("Les nouvelles classes ont correctement ete ajoutee !\n");
            //On incrémente le nombre de classes de la section
            tab->nbrAnnees += nbrAnneeACreer;
            sauverFichierParametrage(*tab);
            for(i=0; i<nbrAnneeACreer+tab->nbrAnnees; i++)
                printf("Nom : %s", tab->tabAnnees[i].nomAnneeSection);

        }

        else
        {
            printf("Nombre d'annee souhaitee : ");
            scanf("%d", &nbrAnneeACreer);
            tab->tabAnnees = malloc(nbrAnneeACreer * sizeof(T_Annee));
            if(tab == NULL)
            {
                printf("Erreur memoire");
                exit(0);
            }

            for(i = 0 ; i < nbrAnneeACreer ; i++)
                tab->tabAnnees[i] = demanderInfo(tab->tabAnnees[i]);

            printf("Voulez vous sauvegader ce fichier de parametrage ? : ");
            fflush(stdin);
            scanf("%c", &choixSauver);

            if(choixSauver == 'o' || choixSauver == 'O')
            {
                sauverFichierParametrage(*tab);
            }
            else if(choixSauver == 'n' || choixSauver == 'N')
            {
                effacerEcran();
                //administrationAnnees(tab->tabAnnees);
            }


            free(tab->tabAnnees);
        }
    }


    else if(choix == 1)
    {
        printf("Chargement des classes effectue.\n\n");
        system("Pause");
        effacerEcran();
        afficherMenuChoixAnnee(tab);
    }

}
