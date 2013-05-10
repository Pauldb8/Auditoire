/*
 * sauvegardeFichier.c
 *
 *  Created on: 10 mai 2013
 *      Author: Pauldb
 */

#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

#define DEBUG 1
#define TAILLE_MAX 51
#define INCREMENTALLOC 3
#define FICHIER_PARAMETRAGE "Sauvegardes/fichierParametrage.txt"


/*Permet d'enregistrer TOUT le fichier de parametrage*/
void sauverFichierParametrage(T_AnneeSection * tab, int nbr)
{
    FILE *f = NULL;
    int i = 0, j = 0, k = 0;


    f = fopen(FICHIER_PARAMETRAGE, "w+");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s\n", FICHIER_PARAMETRAGE);
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
void chargerFichierParametrage(T_AnneeSection * tab)
{
    int i = 0, j = 0, k, l, m;

    FILE *f = NULL;
    char s[TAILLE_MAX];

    f = fopen(FICHIER_PARAMETRAGE, "rt");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s", FICHIER_PARAMETRAGE);
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
      tab[i].nbClasses = atoi(strtok(NULL, ";")); if(DEBUG) printf("Nombre de classes : %d\n", tab[i].nbClasses);

      tab[i].nomClasse = (char **) malloc(tab[i].nbClasses * sizeof(char*));

      for(l = 0 ; l < tab[i].nbClasses ; l++)
        tab[i].nomClasse[l] = (char *) malloc(TAILLE_MAX * sizeof(char));

     for(k = 0 ; k < tab[i].nbClasses ; k++)
      {
          strcpy(tab[i].nomClasse[k], strtok(NULL,";")); if (DEBUG) printf("Classe : %s\n", tab[i].nomClasse[k]);
      }

      tab[i].nbCoursParEtudiant = atoi(strtok(NULL, ";")); if(DEBUG) printf("Nombre de Cours : %d\n", tab[i].nbCoursParEtudiant);
      tab[i].tabCours = malloc(tab[i].nbCoursParEtudiant * sizeof(T_Cours));

      for(m = 0 ; m < tab[i].nbCoursParEtudiant ; m++)
      {
        strcpy(tab[i].tabCours[m].nomCours, strtok(NULL, ";"));
        tab[i].tabCours[m].ponderation = atoi(strtok(NULL, ";"));
        if(DEBUG)
        {
            printf("Cours %d : %s\n", m, tab[i].tabCours[m].nomCours);
            printf("Ponderation %d : %d\n", m, tab[i].tabCours[m].ponderation);
        }

      }

      if(DEBUG) printf("\n");

      j++;
   }
}

