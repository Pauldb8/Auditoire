/*
 * sauvegardeFichier.c
 *
 *  Created on: 10 mai 2013
 *      Author: Pauldb
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h> //traitement des erreurs pour fopen
#include <string.h>

extern int errno ;

#include "structures.h"
#include "defines.h"

int recupererNombreAnnneeSection()
{
    FILE *f = NULL;
    char s[TAILLE_MAX];

    f = fopen(FICHIER_PARAMETRAGE, "rt");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", FICHIER_PARAMETRAGE);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
    }

    /*On récupère le nombre d'annee/Section*/
    fgets(s, TAILLE_MAX, f);
    int nbr = atoi(s);

    return nbr;
}

/*Permet d'enregistrer TOUT le fichier de parametrage*/
void sauverFichierParametrage(T_Annee * tab, int nbr)
{
    FILE *f = NULL;
    int i = 0, j = 0, k = 0;


    f = fopen(FICHIER_PARAMETRAGE, "w+");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", FICHIER_PARAMETRAGE);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
    }

    fprintf(f, "%d;\n", nbr); // Ecriture du nombre total d'années/sections.

    for(i = 0 ; i < nbr ; i++)
    {
        fprintf(f, "%s;", tab[i].nomAnneeSection);
        fprintf(f, "%d;", tab[i].nbClasses);
        for(j = 0 ; j < tab[i].nbClasses ; j++)
        {
            fprintf(f, "%s;", tab[i].nomClasse[j]);
        }

        fprintf(f, "%d;", tab[i].nbCoursParEtudiant);
        for(k = 0 ; k < tab[i].nbCoursParEtudiant ; k++)
        {
            fprintf(f, "%s;", tab[i].tabCours[k].nomCours);
            fprintf(f, "%d;", tab[i].tabCours[k].ponderation);
        }

        fprintf(f, "\n");
    }

    fclose(f);
}

/*Permet de charger TOUT le fichier de parametrage*/
/*tab contiendra les informations relatives à toutes les années/sections*/

/*
 * @chargerFichierParametrage(char*, T_Annee*): Cette fonction lit un fichier de section
 * et remplit la structure T_Annee, reçue en paramètre, selon les informations
 * du fichier. Le fichier à lire est reçu en paramètre, et est considéré comme
 * étant VALIDE.
 * @param: L'adressse du fichier à charger.
 * @param: un pointeur vers une strucutre T_Annee à remplir avec les infos du fichier.
 * @return: Elle retourne le nombre d'année de la section que contenait le fichier.
 */
int chargerFichierParametrage(char* fichier, T_Annee * tab)
{
    int i = 0, j = 0, k, l, m;

    FILE *f = NULL;
    char s[TAILLE_MAX];
    char urlComplet[TAILLE_MAX] = strcat((char*)URI_FICHIERS, fichier);

    if(DEBUG){
    	printf("urlComplet = %s", urlComplet);
    }

    f = fopen(urlComplet, "rt");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s", urlComplet);
        exit(0);
    }

    /*On récupère le nombre d'annee/Section*/
    fgets(s, TAILLE_MAX, f);
    int nbrAnneeSection = atoi(s);


    /*Mallocage de départ*/
    tab->tabClasse = malloc (INCREMENTALLOC * sizeof(T_Classe));
    tab->tabCours = malloc (INCREMENTALLOC * sizeof(T_Cours));

    /*Initialisation*/
    tab->nbClasses = 0;

    while(fgets(s, TAILLE_MAX, f) != NULL) // Tant que l'on parvient à écrire dans le fichier
   {
      strcpy(tab[j].nomAnneeSection, strtok(s,";")); if(DEBUG) printf("Nom Annee/section : %s\n", tab[j].nomAnneeSection);
      tab[j].nbClasses = atoi(strtok(NULL, ";")); if(DEBUG) printf("Nombre de classes : %d\n", tab[j].nbClasses);

      tab[j].nomClasse = (char **) malloc(tab[j].nbClasses * sizeof(char*));
      if(tab[j].nomClasse == NULL)
        exit(0);

      for(l = 0 ; l < tab[j].nbClasses ; l++)
      {
          tab[j].nomClasse[l] = (char *) malloc(TAILLE_MAX * sizeof(char));
          if(tab[j].nomClasse[l] == 0)
            exit(0);
      }


      for(k = 0 ; k < tab[j].nbClasses ; k++)
      {
          strcpy(tab[j].nomClasse[k], strtok(NULL,";")); if (DEBUG) printf("Classe %d : %s\n", k,  tab[j].nomClasse[k]);
      }

      tab[j].nbCoursParEtudiant = atoi(strtok(NULL, ";")); if(DEBUG) printf("Nombre de Cours : %d\n", tab[j].nbCoursParEtudiant);
      tab[j].tabCours = malloc(tab[j].nbCoursParEtudiant * sizeof(T_Cours));
      if(tab[j].tabCours == 0)
        exit(0);

      for(m = 0 ; m < tab[j].nbCoursParEtudiant ; m++)
      {
        strcpy(tab[j].tabCours[m].nomCours, strtok(NULL, ";"));
        tab[j].tabCours[m].ponderation = atoi(strtok(NULL, ";"));
        if(DEBUG)
        {
            printf("Cours %d : %s\n", m, tab[j].tabCours[m].nomCours);
            printf("Ponderation %d : %d\n", m, tab[j].tabCours[m].ponderation);
        }

      }

      if(DEBUG) printf("\n");

      j++;
   }
    return nbrAnneeSection;
}
