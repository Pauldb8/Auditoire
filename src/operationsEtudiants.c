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
	FILE *fichier;
	char* url;
	int nbEtu = classe.nbEtu;
	url = malloc(MAX_CHAR * sizeof(char));//malloc de l'url

	//G�n�ration de l'url
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES ,nomSection, nomAnnee, classe.nomClasse);
	if(DEBUG)
		printf("\n\nURL : %s\n\n", url);

	//Ouverture du fichier
	fichier = fopen(url, "wb+");
	if(fichier == NULL){
		printf("Erreur lors de l'ouverture de %s\n", url);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
	}
	else{//Enregistrement dans le fichier
		fwrite(&classe, sizeof(T_Classe), 1, fichier);
		fwrite(classe.eleves, (sizeof(T_Etudiant)*nbEtu), 1, fichier);
		printf("Fichier correctement enregistre !");
		system("PAUSE");
	}
}

/*
 * chargerClasse(url, nomClasse): Cette fonction re�oit une URL de fichier binaire
 * contenant toutes les informations d'une classe, elle les charge dans une strucutre
 * de type T_Classe et les renvoit.
 * @param : url du fichier binaire.
 * @param : nom de la classe que l'on cr�e
 * @return : un strucutre de type T_Classe remplie du fichier binaire.
 */
T_Classe chargerClasse(char *url, char* nomClasse){
	FILE *fichier = NULL;
	T_Classe returnClasse;
	T_Classe *returnClasseVide = NULL;
	T_Etudiant *eleves = NULL;
	int nbEtu;

	fichier = fopen(url, "rb");
	if(fichier == NULL){
		returnClasseVide = (T_Classe*) malloc(sizeof(T_Classe));

		//Si le fichier de chargement de classe n'existe pas
		//On cr�e une classe vide avec son nom et le nombre d'�tudiant � 0.
		strcpy(returnClasseVide->nomClasse, nomClasse);
		returnClasseVide->nbEtu = 0;

		printf("La classe \"%s\" est vide, vous devrez la remplir.", nomClasse);
		return *returnClasseVide;
	}
	else{//On lit d'abord la classe, comme cela on sait le nombre d'�tudiants � malloc.
		fread(&returnClasse, sizeof(T_Classe), 1, fichier);
		nbEtu = returnClasse.nbEtu;
		fread(eleves, (sizeof(T_Etudiant)*nbEtu), 1, fichier);
		returnClasse.eleves = malloc(sizeof(T_Etudiant) * nbEtu);
		returnClasse.eleves = eleves;
		//printf(" et ces etudiants sont : %s et %s", returnClasse.eleves[0].prenom, returnClasse.eleves[1].prenom);
		return returnClasse;
	}
}

/*
 * afficherClasse(T_Classe): Cette fonction affiche tous les �l�ves ainsi que leurs
 * ainsi que leur matricule et permet d'en choisir un pour le modifier/visualiser/supprimer.
 * @param: La structure classe � afficher.
 */
void afficherClasse(T_Classe classe){
	int i;
	effacerEcran();
	printf("***Etudiants de la classe \"%s\"***\n", classe.nomClasse);
	printf("Matricule\t\tNom\t\tPrenom\t\t");
	for(i = 0; i < classe.nbEtu; i++){
		printf("\n%s\t\t%s\t\t%s", classe.eleves[i].matricule, classe.eleves[i].nom, classe.eleves[i].prenom);
	}
	//printf("\nnomClasse = %s\n", a.nomClasse);
}


/**
 * Affiche un menu de choix des options possibles sur la classe.
 */
void administrationClasse(char* nomClasse, char* nomSection, char* nomAnnee){
	int choix;
	char* url;
	T_Classe classe;

	effacerEcran();
	//Chargement du fichier de la classe SI existant
    url = malloc(MAX_CHAR * sizeof(char));
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES, nomSection, nomAnnee, nomClasse);
	classe = chargerClasse(url, nomClasse); //Chargement de la classe

	printf("***Gestion d'une classe***\n");
	printf("Classe %s correctement charg�e : ", classe.nomClasse);
	printf("il y a %d �tudiants\n\n", classe.nbEtu);
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
			ajouterEtudiant(classe);
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

void ajouterEtudiant(T_Classe * a)
{
    T_Etudiant etu; 
    char recommencer = 0; 
    
    printf("*** Menu d'ajout d'un etudiant dans la classe %s ***\n\n", a->nomClasse);
    
    do{
    printf("Matricule : "); 
    fflush(sttdin); 
    gets(etu.matricule); 
    printf("Nom : "); 
    fflush(sttdin); 
    gets(etu.nom);
    printf("Prenom : "); 
    fflush(sttdin); 
    gets(etu.prenom);
    printf("Ville : "); 
    fflush(sttdin); 
    gets(etu.ville);
    printf("Rue : "); 
    fflush(sttdin); 
    gets(etu.rue);
    printf("Numero de rue : "); 
    fflush(sttdin); 
    etu.num = getNumber(0, 100);
    printf("Code Postal  : "); 
    fflush(sttdin); 
    etu.cp = getNumber(1000, 9999);
    
    a->eleves[a->nbEtu + 1] = etu; 
    a->nbEtu ++; 
    
    printf("Ajouter encore un etudiant ? (o/n) "); 
    scanf("%c", &recommencer);  
    
    }while(recommencer == 'o' || recommencer == 'O'); 


}
