
/*
 * operationsChoix.c
 *
 *  Created on: 11 mai 2013
 *      Author: Pauldb
 */

#include <stdio.h>
#include <stdlib.h>

#include "administrationCours.h"
#include "structures.h"
#include "fichierParametrage.h"
#include "sauvegardeFichier.h"
#include "operationsEtudiants.h"
#include "tools.h"


/**
 * administrationCours(T_Section *, choix): Cette fonction permet d'ajouter/modifier/supprimer/afficher
 * les cours donnés en l'année dont on reçoit le pointeur en paramètre. Elle permet
 * aussi d'en modifier les pondérations.
 * @param: pointeur vers la section qui contient l'année à administrer.
 * @param: l'index dans le tableau section correspondant à l'année choisie.
 */
void administrerCours(T_Section *section, int anneeChoisie){
	int choix;
	do{
		effacerEcran();
		printf("***Gestion des cours de %s***\n\n", section->tabAnnees[anneeChoisie].nomAnneeSection);

		printf("\t1. Afficher les cours et leurs ponderations\n");
		printf("\t2. Ajouter un cours\n");
		printf("\t3. Modifier un cours\n");
		printf("\t4. Supprimer un cours\n");
		printf("\t5. Enregistrer le fichier des cours\n");
		printf("\t6. Retour\n");
		printf("\nVotre choix: ");
		choix = getNumber(1, 6);

		switch(choix){
		case 1:
			effacerEcran();
			afficherCours(section->tabAnnees[anneeChoisie]);
			system("PAUSE");
			break;
		case 2:
			ajouterCours(&section->tabAnnees[anneeChoisie]);

			break;
		case 3:
			modifierCours(&section->tabAnnees[anneeChoisie]);
			break;
		case 4:
			supprimerCours(&section->tabAnnees[anneeChoisie]);
			break;
		case 5:
			sauverFichierParametrage(*section);
			printf("\nEnregistrement effectue !\n");
			system("PAUSE");
			break;
		}
	}while(choix != 6);
}

void afficherMenuChoixClasse(T_Section sct, int choix)
{
    int i, choixAnnee;

    effacerEcran();

    printf("Sur quelle classe de la section %s voulez vous travailler ?\n\n", sct.nom);
    for(i = 0 ; i < sct.tabAnnees[choix].nbClasses ; i++)
        printf("\t%d. %s\n", i+1, sct.tabAnnees[choix].nomClasse[i]);

    printf("\n\t%d. Ou administrer les cours donnes en cette annee", i+1);

    printf("\n\nVotre choix : ");
    choixAnnee = getNumber(1, i+1);

    if(choixAnnee == (i+1))
    	administrerCours(&sct, choix);
    else
    	administrationClasse(sct.tabAnnees[choix].tabClasse[choixAnnee-1].nomClasse, sct.nom, sct.tabAnnees[choix].nomAnneeSection);
}

void afficherMenuChoixAnnee(T_Section * tab)
{
    int i, choix;

    printf("Veuillez choisir une annee a gerer : \n\n");

    for(i = 0 ; i < tab->nbrAnnees ; i++)
        printf("\t%d. %s\n", i+1, tab->tabAnnees[i].nomAnneeSection);

    printf("\nVotre choix : ");
   choix = getNumber(1, tab->nbrAnnees);

    /*tab[choix - 1] car on propose 1 et 2 Ã  la place de 0 et 1, Ã©tant les positions rÃ©elles dans le tableau*/
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
    choix = getNumber(1, 2);


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
            //On incrÃ©mente le nombre de classes de la section
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
        //printf("Chargement des classes effectue.\n\n");
        //system("Pause");
        effacerEcran();
        afficherMenuChoixAnnee(tab);
    }

}

