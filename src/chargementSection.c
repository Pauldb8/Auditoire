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
 * dont le nom est reçu en paramètre. Elle suppose y trouver des fichiers
 * textes valides, contenant chacun des informations sur une section de
 * l'école. Chaque fichier trouvé représentant une section portant le nomdu fichier.
 * Elle permettra ensuite à l'utilisateur de choisir la section à charger.
 * @return: elle ne renvoie rien.
 * @param: un tableau de char, étant le nom du dossier à parcourir.
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
	        	//On passe les deux premières itérations car elles sont toujours
	        	// "." et ".." autrement dit, le dossier courant et le dossier supérieur.
	        	if((i != 1) && (i != 2))
	        		printf("\t%d. %s\n", i-2, ent->d_name);//On affiche les noms de fichiers
	        	i++;
	        }

	        closedir(rep); //Fermeture du répertoire.
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
