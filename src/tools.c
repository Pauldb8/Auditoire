/*
 * tools.c
 *
 *  Created on: 11 mai 2013
 *      Author: Pauldb
 */
#include <stdio.h>
#include <dirent.h> //Pour la lecture des dossiers
#include <errno.h> //traitement des erreurs pour opendir
extern int errno ;


int getNumber(int min, int max){
	int number;
	do{
		scanf("%d", &number);
	}while((number > max) || (number < min));
	return number;
}

/*
 * @effacerEcran: Cette fonction efface l'écran et réaffiche le titre principal.
 * @param: aucun.
 * @return: aucun.
 */
void effacerEcran(){
	system("CLS");
	printf("***BIENVENUE AU PROGRAMME D'ADMINISTRATION DE L'EPHEC***\n");
}

/*
 * @nombreDeFichier(char*): Cette fonction compte le nombre de fichier présent dans
 * le dossier reçu en paramètre.
 * /!\ Elle retourne cette valeur diminuée de 2 /!\
 * Car les fichiers "." et ".." ne sont autre que des dossiers (le courant et le supérieur)
 * @return: elle retourne le nombre exact de fichier (sans "." et "..").
 */
int nombreDeFichier(char* dossier){
DIR * rep = opendir(dossier);
int nbrSection = 0;

if (rep != NULL)//Dossier correctement ouvert
	{
	struct dirent * ent;
	while ((ent = readdir(rep)) != NULL)//Parcours du dossier
			nbrSection++;	//On incrément à chaque fichier trouvé.
	closedir(rep); //Fermeture du répertoire.
	}
else //Impossible d'ouvrir le dossier : ERREUR.
	{
	printf("Erreur lors de l'ouverture de %s\n", dossier);
	perror ("The following error occurred");
	printf( "Value of errno: %d\n", errno );
	exit(0);
	}
return (nbrSection-2);
//On fait moins 2 pour passer les deux premières itérations car elles sont toujours
// "." et ".." autrement dit, le dossier courant et le dossier supérieur.
}
