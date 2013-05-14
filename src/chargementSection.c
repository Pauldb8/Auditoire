/*
 * chargementSection.c
 *
 *  Created on: 11 mai 2013
 *      Author: Pauldb
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> //Pour la lecture des dossiers
#include <errno.h> //traitement des erreurs pour opendir
#include <unistd.h> //Pour les Sleeps
#include <string.h> //Pour op�ration sur les string

/*Inclusions des headers*/
#include "tools.h"
#include "sauvegardeFichier.h"
#include "defines.h"
#include "structures.h"

extern int errno ;

/*
 * @choisirSectionACharger(char*): cette fonction va parcourir le dossier
 * dont le nom est re�u en param�tre. Elle suppose y trouver des fichiers
 * textes valides, contenant chacun des informations sur une section de
 * l'�cole. Chaque fichier trouv� repr�sentant une section portant le nom du fichier.
 * Elle permettra ensuite � l'utilisateur de choisir la section � charger.
 * @return: T_Section.
 * @param: un tableau de char, �tant le nom du dossier � parcourir.
 */

T_Section choisirSectionACharger(char * dossier)
{
	DIR * rep = opendir(dossier);
	int i = 0, j = 0, nbrSection, numChoisi, nbrAnnees, taille;
	char** sections; //Matrice 2D, premi�re dimension le nombre de section et 2eme leurs noms.
	T_Section sectionChargee;
	T_Annee * anneesChargees;

	effacerEcran();

	printf("*** Choix de Section ***\n\n");
	printf("Voici les sections disponibles :\n\n");
	nbrSection = nombreDeFichier(dossier); //On compte le nombre de fichier

	//Chaque fichier repr�sente une section, on alloue la m�moire pour chaque nom de section
	sections = (char**)malloc(nbrSection * sizeof(char*));
	if(sections == NULL)
    {
        printf("Erreur memoire !\n");
        system("Pause");
        exit(0);
    }

	if (rep != NULL)//Dossier correctement ouvert
	{
		struct dirent * ent;

		while ( (ent = readdir(rep)) != NULL )
		{
			/*On passe les deux premi�res it�rations car elles sont toujours*/
			/* "." et ".." autrement dit, le dossier courant et le dossier sup�rieur.*/
            if((i != 0) && (i != 1))
            {
				printf("\t%d. %s\n", j+1, ent->d_name);//On affiche les noms de fichiers

				sections[j] = (char*)malloc(sizeof(char) * MAX_CHAR);
				if(sections[j] == NULL)
                {
                    printf("Erreur memoire !\n");
                    system("Pause");
                    exit(0);
                }

				strcpy(sections[j], ent->d_name);
				j++;
			}
            i++;
		}

		closedir(rep); //Fermeture du r�pertoire

		//On demande de choisir le dossier
		printf("\n\t%d. Retour",j+1);

        /*-1 car on propose les choix 1, 2 et 3 au lieu de 0, 1 et 2, position r�el dans le tableau*/
		printf("\n\nVotre choix : ");
		numChoisi = (getNumber(1,j+1) - 1);

		if(numChoisi == j)
            main();

		//Chargement des ann�es du fichiers
		anneesChargees = malloc(nbrSection * sizeof(T_Annee));
		nbrAnnees = chargerFichierParametrage(sections[numChoisi], anneesChargees);

		if(DEBUG)
			printf("\n\tnbrAnnees = %d", nbrAnnees);

		//Cr�ation de la section correspondante
		sectionChargee.nbrAnnees = nbrAnnees;
		sectionChargee.tabAnnees = malloc(nbrAnnees * sizeof(T_Annee));
        sectionChargee.tabAnnees = anneesChargees;


		//On supprime l'extension (Informatique.txt => Informatique)
		taille = strlen(sections[numChoisi]);
	    sections[numChoisi][taille - 4] = '\0';
		strcpy(sectionChargee.nom, sections[numChoisi]);

		//On retourne la section charg�e.
		printf("\n\nSection %s correctement chargee !\n", sectionChargee.nom);
		system("PAUSE");

		return sectionChargee;

	}

	else //Impossible d'ouvrir le dossier : ERREUR.
	{
		printf("Erreur lors de l'ouverture de %s\n", dossier);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
	}


}

