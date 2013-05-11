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

#define INCREMENTALLOC 3

void afficherMenuGlobal(T_Annee * tab)
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
        tab = malloc(nbrAnneeSection * sizeof(T_Annee));
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
        int nbr = recupererNombreAnnneeSection();
        tab = malloc(nbrAnneeSection * sizeof(T_Annee));
        chargerFichierParametrage(tab);
        printf("Chargement effecue\n\n");
        system("Pause");
        system("cls");
        afficherMenuChoixSection(tab, nbr);
    }

}

void afficherMenuChoixSection(T_Annee * tab, int nbr)
{
    int i, choix;
    printf("Sur quel annee/section voulez vous travailler ?\n\n");
    for(i = 0 ; i < nbr ; i++)
        printf("\t%d. %s\n", i+1, tab[i].nomAnneeSection);

    printf("\nVotre choix : ");
    scanf("%d", &choix);

    /*tab[choix - 1] car on propose 1 et 2 à la place de 0 et 1, étant les positions réelles dans le tableau*/
    afficherMenuChoixClasse(tab[choix - 1]);
}

void afficherMenuChoixClasse(T_Annee a)
{
    system("cls");
    int i, choix = 0;

    printf("Sur quelle classe de la section %s voulez vous travailler ?\n\n", a.nomAnneeSection);
    for(i = 0 ; i < a.nbClasses ; i++)
        printf("\t%d. %s\n", i+1, a.nomClasse[i]);

    printf("\nVotre choix : ");
    scanf("%d", &choix);


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



