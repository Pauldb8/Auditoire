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

    /*On r�cup�re le nombre d'annee/Section*/
    fgets(s, TAILLE_MAX, f);
    int nbr = atoi(s);

    return nbr;
}

/*Permet d'enregistrer TOUT le fichier de parametrage*/
void sauverFichierParametrage(T_Section section)
{
    FILE *f = NULL;
    char *fichier = section.nom;
    int nbr = section.nbrAnnees;
    T_Annee * tab = section.tabAnnees;
    char *urlComplet;
    int i = 0, j = 0, k = 0;

    sprintf(urlComplet,"%s%s.txt",URL_SECTIONS,fichier); //Concat�nation URLDOSSIER+URLFICHIER

    if(DEBUG)
    	printf("\nurlComplet = %s\n", urlComplet);

    f = fopen(urlComplet, "w+");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", urlComplet);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
    }

    fprintf(f, "%d;\n", nbr); // Ecriture du nombre total d'ann�es/sections.

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
/*tab contiendra les informations relatives � toutes les ann�es/sections*/

/*
 * @chargerFichierParametrage(char*, T_Annee*): Cette fonction lit un fichier de section
 * et remplit la structure T_Annee, re�ue en param�tre, selon les informations
 * du fichier. Le fichier � lire est re�u en param�tre, et est consid�r� comme
 * �tant VALIDE.
 * @param: L'adressse du fichier � charger.
 * @param: un pointeur vers une strucutre T_Annee � remplir avec les infos du fichier.
 * @return: Elle retourne le nombre d'ann�e de la section que contenait le fichier.
 */
int chargerFichierParametrage(char* fichier, T_Annee * tab)
{
    int j = 0, k, l, m;

    FILE *f = NULL;
    char s[TAILLE_MAX];
    char *url1 = URI_FICHIERS;
    char urlComplet[MAX_CHAR];

    sprintf(urlComplet,"%s%s",url1,fichier); //Concat�nation URLDOSSIER+URLFICHIER

    if(DEBUG)
    	printf("\nurlComplet = %s\n", urlComplet);


    f = fopen(urlComplet, "rt");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s", urlComplet);
        exit(0);
    }

    /*On r�cup�re le nombre d'annee/Section*/
    fgets(s, TAILLE_MAX, f);
    int nbrAnneeSection = atoi(s);

    while(fgets(s, TAILLE_MAX, f) != NULL) // Tant que l'on parvient � �crire dans le fichier
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

