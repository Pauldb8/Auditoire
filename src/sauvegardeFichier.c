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


/*Permet d'enregistrer TOUT le fichier de parametrage*/
void sauverFichierParametrage(T_Section section)
{
    FILE *f = NULL;
    char *fichier = section.nom;
    int nbr = section.nbrAnnees;
    T_Annee * tab = section.tabAnnees;
    char urlComplet[MAX_CHAR];
    int i = 0, j = 0, k = 0;

    sprintf(urlComplet,"%s%s.txt",URL_SECTIONS,fichier); //Concaténation URLDOSSIER+URLFICHIER

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
    if(DEBUG)
    	printf("Fichier correctement ouvert en ecriture\n");

    fprintf(f, "%d;\n", nbr); // Ecriture du nombre total d'années/sections.
    if(DEBUG)
    	printf("nbAnnee = %d\n", nbr);

    for(i = 0 ; i < nbr ; i++)
    {
        fprintf(f, "%s;", tab[i].nomAnneeSection);//Nom annee
        fprintf(f, "%s;", tab[i].abbreviation);//Abbreviation
        fprintf(f, "%d;", tab[i].compteurMatricule);//Nom annee
        fprintf(f, "%d;", tab[i].nbClasses);//Nombre de classe dans l'année

        if(DEBUG)
        {
        	printf("nom Section %s, nombre de classe : %d\n", tab[i].nomAnneeSection, tab[i].nbClasses);
        	printf("Classes:\n");
        }

        for(j = 0 ; j < tab[i].nbClasses ; j++)
        {
            fprintf(f, "%s;", tab[i].nomClasse[j]);

            if(DEBUG)
            	printf("\t%s\n", tab[i].nomClasse[j]);
        }

        fprintf(f, "%d;", tab[i].nbCoursParEtudiant);
        if(DEBUG)
        	printf("nbCoursParEtudiant = %d\nCours:\n", tab[i].nbCoursParEtudiant);
        for(k = 0 ; k < tab[i].nbCoursParEtudiant ; k++)
        {
            fprintf(f, "%s;", tab[i].tabCours[k].nomCours);
            fprintf(f, "%d;", tab[i].tabCours[k].ponderation);
            if(DEBUG)
            	printf("\t%s (%d)", tab[i].tabCours[k].nomCours, tab[i].tabCours[k].ponderation);
        }

        fprintf(f, "\n");
    }

    fclose(f);
}


/*
 * @chargerFichierParametrage(char*): Cette fonction lit un fichier de section
 * et retourne une structure T_Section chargée selon les informations
 * du fichier. Le nom du fichier à lire est reçu en paramètre, et est considéré comme
 * étant VALIDE.
 * @param: L'adressse du fichier à charger.
 * @return: Elle retourne la structure crée à partir du fichier.
 */
T_Section chargerFichierParametrage(char* fichier)
{
    int j = 0, k, l, m;
    T_Section sectionChargee;
    T_Annee *tab;

    FILE *f = NULL;
    char s[TAILLE_MAX];
    char *url1 = URI_FICHIERS;
    char urlComplet[MAX_CHAR];

    sprintf(urlComplet,"%s%s",url1,fichier); //Concaténation URLDOSSIER+URLFICHIER

    if(DEBUG)
    	printf("\nurlComplet = %s\n", urlComplet);


    f = fopen(urlComplet, "rt");
    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture de %s", urlComplet);
        exit(0);
    }

    /*On récupère le nombre d'annee/Section*/
    fgets(s, TAILLE_MAX, f);
    int nbrAnneeSection = atoi(s);
    sectionChargee.nbrAnnees = nbrAnneeSection;
    sectionChargee.tabAnnees = (T_Annee*) malloc(sizeof(T_Annee) * nbrAnneeSection);
    tab = (T_Annee*) malloc(sizeof(T_Annee) * nbrAnneeSection);

    while(fgets(s, TAILLE_MAX, f) != NULL) // Tant que l'on parvient à lire dans le fichier
   {
      strcpy(tab[j].nomAnneeSection, strtok(s,";")); if(DEBUG) printf("Nom Annee/section : %s\n", tab[j].nomAnneeSection);
      strcpy(tab[j].abbreviation, strtok(NULL,";")); if(DEBUG) printf("Abbreviation : %s\n", tab[j].abbreviation);
      tab[j].compteurMatricule = atoi(strtok(NULL,";")); if(DEBUG) printf("Compteur matricule : %d\n", tab[j].compteurMatricule);
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

      tab[j].tabClasse = malloc(tab[j].nbClasses * sizeof(T_Classe));
      for(l = 0; l < tab[j].nbClasses; l++){
    	  strcpy(tab[j].tabClasse[l].nomClasse, tab[j].nomClasse[l]);
      }

      if(DEBUG) printf("\n");

      j++;
   }
    sectionChargee.tabAnnees = tab;
    return sectionChargee;
}

