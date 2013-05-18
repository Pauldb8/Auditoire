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

		if(number < min || number > max)
        {
            printf("Nombre entre incorrect, veulliez recommencer : ");
            scanf("%d", &number);
        }

	}while((number > max) || (number < min));
	return number;
}


/*
 * @effacerEcran: Cette fonction efface l'�cran et r�affiche le titre principal.
 * @param: aucun.
 * @return: aucun.
 */
void effacerEcran(){
	system("CLS");
	printf("*** Programme d'administration d'une ecole ***\n\n");
}

/*
 * @nombreDeFichier(char*): Cette fonction compte le nombre de fichier pr�sent dans
 * le dossier re�u en param�tre.
 * /!\ Elle retourne cette valeur diminu�e de 2 /!\
 * Car les fichiers "." et ".." ne sont autre que des dossiers (le courant et le sup�rieur)
 * @return: elle retourne le nombre exact de fichier (sans "." et "..").
 */
int nombreDeFichier(char* dossier)
{
    DIR * rep = opendir(dossier);
    int nbrSection = 0;

    if (rep != NULL)//Dossier correctement ouvert
    {
	struct dirent * ent;

	while ((ent = readdir(rep)) != NULL)//Parcours du dossier
			nbrSection++;	//On incr�ment � chaque fichier trouv�.

	closedir(rep); //Fermeture du r�pertoire.
	}

    else //Impossible d'ouvrir le dossier : ERREUR.
	{
        printf("Erreur lors de l'ouverture de %s\n", dossier);
        perror ("The following error occurred");
        printf( "Value of errno: %d\n", errno );
        exit(0);
	}

	/*On fait moins 2 pour passer les deux premi�res it�rations car elles sont toujours*/
    /*"." et ".." autrement dit, le dossier courant et le dossier sup�rieur.*/
    return (nbrSection-2);

}

