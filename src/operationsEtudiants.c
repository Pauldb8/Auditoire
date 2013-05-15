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

	T_Etudiant etudiants[2];
	strcpy(etudiants[0].matricule, "HE201089");
	strcpy(etudiants[0].nom, "De Buck");
	strcpy(etudiants[0].prenom, "Paul");
	for(i = 0; i < 5; i ++)
		etudiants[0].tabCotes[i] = 0;
	etudiants[0].moyennePourcentage = 19.0;

	strcpy(etudiants[1].matricule, "HE201089");
	strcpy(etudiants[1].nom, "De Buck");
	strcpy(etudiants[1].prenom, "Paul");
	for(i = 0; i < 5; i ++)
		etudiants[1].tabCotes[i] = 0;
	etudiants[1].moyennePourcentage = 19.0;

	classeTemp.classe = (T_Etudiant*) malloc( 2* sizeof(T_Etudiant));
	classeTemp.classe[0] = etudiants[0];
	classeTemp.classe[1] = etudiants[1];

	//Enregistrement
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES ,nomSection, nomAnnee, classe.nomClasse);
	if(DEBUG)
		printf("\n\nURL : %s\n\n", url);
	fichier = fopen(url, "wb");
	if(fichier == NULL){
		printf("Erreur lors de l'ouverture de %s\n", url);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
	}
	else{
		fwrite(&classe, sizeof(T_Classe), 1, fichier);
		fclose(fichier);
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
	T_Classe *returnClasse;
	fichier = fopen(fichier, "rb");
	if(fichier == NULL){
		printf("La classe est vide, vous devrez la remplir.");
		returnClasse = (T_Classe*) malloc(sizeof(T_Classe));
		strcpy(returnClasse->nomClasse, nomClasse);
	}
	else{
		fread(returnClasse, sizeof(T_Classe), 1, fichier);
		printf("Classe %s correctement chargée : ", returnClasse->nomClasse);
		printf("il y a %d étudiants", returnClasse->nbEtu);
		fclose(fichier)
	}
	return *returnClasse;
}

/**
 * Affiche un menu de choix des options possibles sur la classe.
 */
void administrationClasse(T_Classe *classe, char* nomSection, char* nomAnnee){
	int choix;
	effacerEcran();
	char *url;
	//Chargement du fichier de la classe SI existant
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES ,nomSection, nomAnnee, classe->nomClasse);
	*classe = chargerClasse(url, classe->nomClasse);
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
		case 6:
			printf("%s", nomSection); system("PAUSE");
			sauvegarderClasse(*classe, nomSection, nomAnnee);
			break;
	}

}
