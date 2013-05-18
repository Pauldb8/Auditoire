/*
 * administrationCours.c
 *
 *  Created on: 18 mai 2013
 *      Author: Pauldb
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "tools.h"

/*
 * affichercours(T_Annee): Cette fonction affiche les cours et leurs pond�rations d'une
 * classe re�ue en param�tre.
 * @param: Une structure T_Annee avec un tableau de Cours � afficher.
 */
void afficherCours(T_Annee annee){
	int i;

	printf("***Cours des %s***\n", annee.nomAnneeSection);
	printf("\t   Nom\t\tPonderation\n");
	for(i = 0; i < annee.nbCoursParEtudiant; i++)
		printf("\t%d. %s\t\t%d\n", i+1, annee.tabCours[i].nomCours, annee.tabCours[i].ponderation);
	printf("\n");
}

/*
 * ajouterCours(T_Annee*): cette fonction permet d'ajouter un cours
 * � l'ann�e choisie, elle s'occupe d'allouer la m�moire.
 * @param: Un pointeur sur l'ann�e dont on veut ajouter un cours.
 */
void ajouterCours(T_Annee* annee){
	char nomCours[MAX_CHAR];
	int ponderationCours, nbCours = annee->nbCoursParEtudiant;
	T_Cours nouveauCours;
	effacerEcran();
	printf("***Ajout d'un cours a %s***\n\n", annee->nomAnneeSection);
	printf("Entrez le nom du cours a ajouter : ");
	scanf("%s", nomCours);
	printf("Entrez sa ponderation : ");
	scanf("%d", &ponderationCours);
	strcpy(nouveauCours.nomCours, nomCours);
	nouveauCours.ponderation = ponderationCours;

	//Allocation de la place n�cessaire, 1 cours en plus
	annee->tabCours = (T_Cours *) realloc(annee->tabCours, (nbCours+1) * sizeof(T_Cours));
	annee->tabCours[nbCours] = nouveauCours;
	annee->nbCoursParEtudiant++;
	printf("\nLe cours %s (%d) a correctement ete ajoute !\n", annee->tabCours[nbCours].nomCours, annee->tabCours[nbCours].ponderation);
	system("PAUSE");
}

/*
 * modificationCours(T_Annee*): cette fonction permet de choisir parmis les cours
 * et d'en modifier le nom ou la pond�ration.
 * @param: elle prend en param�tre le pointeur vers l'annee.
 */
void modifierCours(T_Annee* annee){
	int choix;
	char nomCours[MAX_CHAR];

	effacerEcran();
	afficherCours(*annee);
	printf("\nQuel cours souhaitez-vous modifier : ");
	choix = getNumber(1, annee->nbCoursParEtudiant);
	printf("Tapez le nouveau nom pour %s : ", annee->tabCours[choix-1].nomCours);
	scanf("%s", nomCours);
	strcpy(annee->tabCours[choix-1].nomCours, nomCours);
	printf("Tapez la nouvelle pond�ration (anciennement %d) : ", annee->tabCours[choix-1].ponderation);
	annee->tabCours[choix-1].ponderation = getNumber(1, 60); //Pas plus que 60 cr�dit pour un cours !
	printf("Le cours \"%s (%d)\" a ete correctement modifie.\n", annee->tabCours[choix-1].nomCours, annee->tabCours[choix-1].ponderation);
	system("PAUSE");
}
