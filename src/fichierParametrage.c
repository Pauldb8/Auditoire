#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Permet de créer 1 anneeSection */
T_Annee demanderInfo(T_Annee anneeSection, char *abbr)
{
    system("cls");
    printf("**** Creation d'annee **** \n\n");
    char abbrAnnee[2];

    int i = 0;

        printf("Nom (ex : 1TI) : ");
        scanf("%s", anneeSection.nomAnneeSection);
        printf("Nombre de Classes : ");
        scanf("%d", &anneeSection.nbClasses);

        anneeSection.tabClasse = (T_Classe *)malloc(anneeSection.nbClasses * sizeof(T_Classe));
        if(anneeSection.tabClasse == NULL)
            exit(0);

        anneeSection.nomClasse = (char **)malloc(anneeSection.nbClasses * sizeof(char*));
        if(anneeSection.nomClasse == NULL)
            exit(0);

        for(i = 0 ; i < anneeSection.nbClasses ; i++)
        {
            anneeSection.nomClasse[i] = (char *)malloc(MAX_CHAR * sizeof(char));
            if(anneeSection.nomClasse[i] == NULL)
                exit(0);
            printf("\t Nom de la classe %d (ex : 1TM1) : ", i+1);
            scanf("%s", anneeSection.nomClasse[i]);
        //On demande le format de matricule
            printf("\t\t\t-Abbreviation pour les matricules de la classe (ex: %s10): ", abbr);
		   do{
				printf("%s", abbr);//HE
				scanf("%s", abbrAnnee);//10
		   }while(strlen(abbrAnnee) > 2);
		   sprintf(anneeSection.abbreviation, "%s%s", abbr, abbrAnnee);//Création du type de matricule HE10XXXX par ex.
        }

        printf("\n");

        printf("Nombre de cours par etudiant : ");
        scanf("%d", &anneeSection.nbCoursParEtudiant);

        anneeSection.tabCours = malloc(anneeSection.nbCoursParEtudiant * sizeof(T_Cours));
        if(anneeSection.tabCours == NULL)
            exit(0);

        for(i = 0 ; i < anneeSection.nbCoursParEtudiant ; i++)
        {
            printf("\t Nom du cours %d : ", i+1);
            scanf("%s", anneeSection.tabCours[i].nomCours);
            printf("\t Ponderation de ce cours : ");
            scanf("%d", &anneeSection.tabCours[i].ponderation);
        }

        printf("\n");

    return anneeSection;

    free(anneeSection.tabClasse);
    free(anneeSection.nomClasse);
    free(anneeSection.tabCours);

    for(i = 0 ; i < anneeSection.nbClasses ; i++)
        free(anneeSection.nomClasse[i]);

}
