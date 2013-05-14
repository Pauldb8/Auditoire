/*
 * operationsEtudiants.c
 *
 *  Created on: 14 mai 2013
 *      Author: Paul
 */
#include "structures.h"
#include "stdio.h"
#include "stdlib.h"
#include "tools.h"
#include "defines.h"
#include "sauvegardeFichier.h"
#include <errno.h> //traitement des erreurs pour fopen

extern int errno ;

/**
 * Affiche un menu de choix des options possibles sur la classe.
 */
void administrationClasse(T_Annee* classe, char* nomSection){
	int choix;
	effacerEcran();
	printf("***Gestion d'une classe***");
	printf("\n\t1. Ajouter un etudiant");
	printf("\n\t2. Modifier un etudiant");
	printf("\n\t3. Supprimer un etudiant");
	printf("\n\t4. Afficher la classe");
	printf("\n\t5. Afficher un classement des etudiants");
	printf("\n\t6. Sauvegarder la classe");
	printf("\n\t7. Retour");
	choix = getNumber(1, 7);
	switch(choix){
		case 1:
			//ajouterEtudiant(classe);
			break;
		case 2:
			sauvegarderClasse(classe, nomSection, classe->nomClasse);
			break;
	}

}


void sauvegarderClasse(T_Classe classe, char *nomSection, char *nomAnnee){
	T_Classe classeTemp;
	strcpy(classeTemp.nomClasse, classe.nomClasse);
	classeTemp.nbEtu = 2;

	FILE *fichier;
	char* url;

	T_Etudiant etudiants[2];
	etudiants[0].matricule = "HE201089";
	etudiants[0].nom = "De Buck";
	etudiants[0].prenom = "Paul";
	etudiants[0].adr = "Blabla";
	for(int i = 0; i < 5; i ++)
		etudiants[0].tabCotes[i] = 0;
	etudiants[0].moyennePourcentage = 19.0;

	etudiants[1].matricule = "HE201090";
	etudiants[1].nom = "Nanson";
	etudiants[1].prenom = "Celien";
	etudiants[1].adr = "Blabla";
	for(int i = 0; i < 5; i ++)
		etudiants[1].tabCotes[i] = 0;
	etudiants[1].moyennePourcentage = 19.0;

	classeTemp.classe = (T_Etudiant*) malloc( 2* sizeof(T_Etudiant));
	classeTemp.classe[0] = etudiants[0];
	classeTemp.classe[1] = etudiants[1];

	//Enregistrement
	sprintf(url, "%s%s.%s.%s.bin", URL_SECTIONS ,nomSection, nomAnnee, classe.nomClasse);
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
