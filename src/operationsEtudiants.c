/*
 * operationsEtudiants.c
 *
 *  Created on: 14 mai 2013
 *      Author: Paul
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> //traitement des erreurs pour fopen
#include "structures.h"
#include "tools.h"
#include "defines.h"
#include "sauvegardeFichier.h"

extern int errno ;

void sauvegarderClasse(T_Classe classe, char *nomSection, char *nomAnnee){
	T_Classe classeTemp;
	strcpy(classeTemp.nomClasse, classe.nomClasse);
	classeTemp.nbEtu = 2;

	FILE *fichier;
	char* url;
	int i;
	url = malloc(MAX_CHAR * sizeof(char));

	T_Etudiant *etudiants;
	etudiants = malloc(2*sizeof(T_Etudiant));
	strcpy(etudiants[0].matricule, "HE201089");
	strcpy(etudiants[0].nom, "Nanson");
	strcpy(etudiants[0].prenom, "Celien");
	for(i = 0; i < 5; i ++)
		etudiants[0].tabCotes[i] = 0;
	etudiants[0].moyennePourcentage = 19.0;

	strcpy(etudiants[1].matricule, "HE201089");
	strcpy(etudiants[1].nom, "De Buck");
	strcpy(etudiants[1].prenom, "Paul");
	for(i = 0; i < 5; i ++)
		etudiants[1].tabCotes[i] = 0;
	etudiants[1].moyennePourcentage = 19.0;

	classeTemp.eleves = (T_Etudiant*) malloc( 2* sizeof(T_Etudiant));
	memcpy(classeTemp.eleves, etudiants, (sizeof(T_Etudiant) * 2));
	printf("Nom etudiant 1 : %s, etudiant 2 : %s\n\n", classeTemp.eleves[0].prenom, classeTemp.eleves[1].prenom);

	//Enregistrement
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES ,nomSection, nomAnnee, classe.nomClasse);
	if(DEBUG)
		printf("\n\nURL : %s\n\n", url);
	fichier = fopen(url, "wb+");
	if(fichier == NULL){
		printf("Erreur lors de l'ouverture de %s\n", url);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
	}
	else{
		fwrite(&classeTemp, (sizeof(T_Classe) + sizeof(T_Etudiant) * 2), 1, fichier);
		printf("Fichier correctement enregistre !");
		system("PAUSE");
	}
}

/*
 * chargerClasse(url, nomClasse): Cette fonction reçoit une URL de fichier binaire
 * contenant toutes les informations d'une classe, elle les charge dans une strucutre
 * de type T_Classe et les renvoit.
 * @param : url du fichier binaire.
 * @param : nom de la classe que l'on crée
 * @return : un strucutre de type T_Classe remplie du fichier binaire.
 */
T_Classe chargerClasse(char *url, char* nomClasse){
	FILE *fichier = NULL;
	T_Classe returnClasse;
	T_Classe *returnClasseVide = NULL;
	printf("Voici l'url : %s\n", url);
	fichier = fopen(url, "rb");
	if(fichier == NULL){
		returnClasseVide = (T_Classe*) malloc(sizeof(T_Classe));

		//Si le fichier de chargement de classe n'existe pas
		//On crée une classe vide avec son nom et le nombre d'étudiant à 0.
		strcpy(returnClasseVide->nomClasse, nomClasse);
		returnClasseVide->nbEtu = 0;

		printf("La classe \"%s\" est vide, vous devrez la remplir.", nomClasse);
		return *returnClasseVide;
	}
	else{
		fread(&returnClasse, sizeof(T_Classe), 1, fichier);
		printf("Classe %s correctement chargée : ", returnClasse.nomClasse);
		printf("il y a %d étudiants", returnClasse.nbEtu);
		printf(" et ces etudiants sont : %s et %s", returnClasse.eleves[0].prenom, returnClasse.eleves[1].prenom);
		return returnClasse;
	}
}

/*
 * afficherClasse(T_Classe): Cette fonction affiche tous les élèves ainsi que leurs
 * notes dans la console.
 * @param: La structure classe à afficher.
 */
void afficherClasse(T_Classe a){
	int i;
	for(i = 0; i < a.nbEtu; i++){
		printf("\nNom eleve %d : %s", (i+1), a.eleves[i].prenom);
	}
}

/**
 * Affiche un menu de choix des options possibles sur la classe.
 */
void administrationClasse(char* nomClasse, char* nomSection, char* nomAnnee){
	int choix;
	char* url;
	T_Classe classe;
	strcpy(classe.nomClasse, nomClasse);

	effacerEcran();
	//Chargement du fichier de la classe SI existant
    url = malloc(MAX_CHAR * sizeof(char));
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES, nomSection, nomAnnee, nomClasse);
	classe = chargerClasse(url, nomClasse);

	printf("\nNom de la classe chargee :");
	printf("***Gestion d'une classe***");
	printf("\n\t1. Ajouter un etudiant");
	printf("\n\t2. Modifier un etudiant");
	printf("\n\t3. Supprimer un etudiant");
	printf("\n\t4. Afficher la classe");
	printf("\n\t5. Afficher un classement des etudiants");
	printf("\n\t6. Sauvegarder la classe");
	printf("\n\t7. Retour\n\n");
	printf("Votre choix : ");
	choix = getNumber(1, 7);
	switch(choix){
		case 1:
			//ajouterEtudiant(classe);
			break;
		case 4:
			afficherClasse(classe);
			break;
		case 6:
			printf("%s", nomSection); system("PAUSE");
			sauvegarderClasse(classe, nomSection, nomAnnee);
			break;
	}

}
