/*
 * administrationCours.c
 *
 *  Created on: 18 mai 2013
 *      Author: Pauldb
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "structures.h"
#include "tools.h"
#include "operationsEtudiants.h"

/*
 * affichercours(T_Annee): Cette fonction affiche les cours et leurs pondérations d'une
 * classe reçue en paramètre.
 * @param: Une structure T_Annee avec un tableau de Cours à afficher.
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
 * à l'année choisie, elle s'occupe d'allouer la mémoire.
 * @param: Un pointeur sur l'année dont on veut ajouter un cours.
 */
void ajouterCours(T_Annee* annee){
	char nomCours[MAX_CHAR];
	int ponderationCours, nbCours = annee->nbCoursParEtudiant;
	if(nbCours < MAX_COURS){
		T_Cours nouveauCours;
		effacerEcran();
		printf("***Ajout d'un cours a %s***\n\n", annee->nomAnneeSection);
		printf("Entrez le nom du cours a ajouter : ");
		scanf("%s", nomCours);
		printf("Entrez sa ponderation : ");
		scanf("%d", &ponderationCours);
		strcpy(nouveauCours.nomCours, nomCours);
		nouveauCours.ponderation = ponderationCours;

		//Allocation de la place nécessaire, 1 cours en plus
		annee->tabCours = (T_Cours *) realloc(annee->tabCours, (nbCours+1) * sizeof(T_Cours));
		annee->tabCours[nbCours] = nouveauCours;
		annee->nbCoursParEtudiant++;
		printf("\nLe cours %s (%d) a correctement ete ajoute !\n", annee->tabCours[nbCours].nomCours, annee->tabCours[nbCours].ponderation);
		system("PAUSE");
	}
	else{
		printf("Impossible : le nombre maximum de cours autorises est atteint (%d cours) !\n", MAX_COURS);

	}
}

/*
 * modificationCours(T_Annee*): cette fonction permet de choisir parmis les cours
 * et d'en modifier le nom ou la pondération.
 * @param: elle prend en paramètre le pointeur vers l'annee.
 */
void modifierCours(T_Annee* annee){
	int choix;
	char nomCours[MAX_CHAR];
	effacerEcran();
	if(annee->nbCoursParEtudiant > 0){
		afficherCours(*annee);
		printf("\t%d. Retour\n", annee->nbCoursParEtudiant+1);
		printf("\nQuel cours souhaitez-vous modifier : ");
		choix = getNumber(1, annee->nbCoursParEtudiant+1);
		if(choix != annee->nbCoursParEtudiant+1){
			printf("Tapez le nouveau nom pour %s : ", annee->tabCours[choix-1].nomCours);
			scanf("%s", nomCours);
			strcpy(annee->tabCours[choix-1].nomCours, nomCours);
			printf("Tapez la nouvelle pondération (anciennement %d) : ", annee->tabCours[choix-1].ponderation);
			annee->tabCours[choix-1].ponderation = getNumber(1, 60); //Pas plus que 60 crédit pour un cours !
			printf("Le cours \"%s (%d)\" a ete correctement modifie.\n", annee->tabCours[choix-1].nomCours, annee->tabCours[choix-1].ponderation);
			system("PAUSE");
		}
	}
	else {
			printf("Il n'y a aucun cours a modifier !\n");
			system("PAUSE");
		}
}

/*
 * supprimerCours(T_Annee*): cette fonction affiche les cours d'une année et permet
 * d'en choisir un à supprimer, elle s'occupe des toutes les allocations dynamiques nécessaires.
 * Elle supprime également le cours dans le tableau de notes des élèves de l'école.
 * @param: pointeur sur l'année à modifier.
 */
void supprimerCours(T_Annee *annee){
	int choix, i, j, k;
	effacerEcran();
	if(annee->nbCoursParEtudiant > 0){
		afficherCours(*annee);
		printf("\t%d. Retour\n", annee->nbCoursParEtudiant+1);
		printf("\nQuel cours souhaitez-vous supprimer : ");
		choix = getNumber(1, annee->nbCoursParEtudiant+1);

		if(choix != annee->nbCoursParEtudiant+1){
			for(i = choix-1; i < annee->nbCoursParEtudiant-1; i++){
				annee->tabCours[i] = annee->tabCours[i+1];
			}

			//On réalloue les mémoires pour une place en moins
			annee->nbCoursParEtudiant--;
			annee->tabCours = (T_Cours *) realloc(annee->tabCours, sizeof(T_Cours) * annee->nbCoursParEtudiant);

			//Maintenant supprimons ce cours du tableau de cotes de TOUS les élèves
			for(i = 0; i < annee->nbClasses; i++){ //Pour chaque classe
				for(j = 0; j < annee->tabClasse[i].nbEtu; j++)//Pour chaque élèves de la classe
				{
					//On descend les notes d'une case d'index, supprimant à partir de l'index que l'on veut supprimer
					for(k = choix - 1; k < annee->nbCoursParEtudiant-1; k++)//Pour chacunes des notes des élèves
						annee->tabClasse[i].eleves[j].tabCotes[k] = annee->tabClasse[i].eleves[j].tabCotes[k+1];
					annee->tabClasse[i].eleves[j].tabCotes = realloc(annee->tabClasse[i].eleves[j].tabCotes, sizeof(double) * annee->nbCoursParEtudiant);
					//Recalcul des moyennes et echecs de tous les élèves étant donné la supression d'un cours
					annee->tabClasse[i].eleves[j].moyennePourcentage = calculerMoyenne(annee->tabClasse[i].eleves[j], annee->nbCoursParEtudiant);
					annee->tabClasse[i].eleves[j].nbEchecs = calculerNombreEchecs(annee->tabClasse[i].eleves[j], annee->nbCoursParEtudiant);
				}
			}

			printf("\nCours correctement supprime !\n");
			system("PAUSE");
		}
	}
	else {
		printf("Il n'y a aucun cours a supprimer !\n");
		system("PAUSE");
	}
}
