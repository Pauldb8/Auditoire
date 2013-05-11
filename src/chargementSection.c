/*
 * chargementSection.c
 *
 *  Created on: 11 mai 2013
 *      Author: Pauldb
 */
#include <stdio.h>
#include <dirent.h> //Pour la lecture des dossiers
#include <errno.h> //traitement des erreurs pour opendir

extern int errno ;

/*
 * @choisirSectionACharger(char*): cette fonction va parcourir le dossier
 * dont le nom est re�u en param�tre. Elle suppose y trouver des fichiers
 * textes valides, contenant chacun des informations sur une section de
 * l'�cole. Chaque fichier trouv� repr�sentant une section portant le nomdu fichier.
 * Elle permettra ensuite � l'utilisateur de choisir la section � charger.
 * @return: elle ne renvoie rien.
 * @param: un tableau de char, �tant le nom du dossier � parcourir.
 */
void choisirSectionACharger(char* dossier){
	DIR * rep = opendir(dossier);
	int i = 1;

	effacerEcran();
	printf("**Choix de Section\n\n**");
	printf("Voici les sections disponibles:\n");
	if (rep != NULL)//Dossier correctement ouvert
	    {
	        struct dirent * ent;

	        while ((ent = readdir(rep)) != NULL)
	        {
	        	//On passe les deux premi�res it�rations car elles sont toujours
	        	// "." et ".." autrement dit, le dossier courant et le dossier sup�rieur.
	        	if((i != 1) && (i != 2))
	        		printf("\t%d. %s\n", i-2, ent->d_name);//On affiche les noms de fichiers
	        	i++;
	        }

	        closedir(rep); //Fermeture du r�pertoire.
	        //On demande de choisir le dossier
	        printf("\n\nVotre choix : ");
	        getNumber(1,i-3);
	    }
	else //Impossible d'ouvrir le dossier : ERREUR.
	    {
	        printf("Erreur lors de l'ouverture de %s\n", dossier);
			perror ("The following error occurred");
			printf( "Value of errno: %d\n", errno );
			exit(0);
	    }
}
