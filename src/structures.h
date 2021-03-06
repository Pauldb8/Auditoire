
/*
 * structures.h
 *
 *  Created on: 10 mai 2013
 *      Author: Paul, Célien And Steeves
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_
#include "defines.h"

typedef struct
{
    char matricule[MAX_CHAR];
    char nom[MAX_CHAR];
    char prenom[MAX_CHAR];
    double *tabCotes;
    double moyennePourcentage;
    int nbEchecs;
    char rue[MAX_CHAR];
    char ville[MAX_CHAR];
    int num;
    int cp;
}T_Etudiant;

typedef struct{
    char nomCours[MAX_CHAR];
    int ponderation;
}T_Cours;

typedef struct{
    char nomClasse[MAX_CHAR];
    int nbEtu;
    T_Etudiant * eleves;
}T_Classe;

// Definition d'une annee/section (1TI)
typedef struct{
    char nomAnneeSection[MAX_CHAR];
    int nbClasses;
    char **nomClasse; // Tableau contenant le nom des classes. (1TM1)
    int nbCoursParEtudiant;
    char abbreviation[4]; //TI10XXXX
    int compteurMatricule;
    T_Cours *tabCours;
    T_Classe *tabClasse; // Tableau de classe, exemple : 1TM1 (on ne sauvegardes pas ce champs dans le .txt mais dans le .bin)
}T_Annee;


//Structure qui contiendra les diff�rentes ann�es de la section
typedef struct{
	char nom[MAX_CHAR];
	char abbreviation[2];//TIXXXXXX
	int nbrAnnees;
	T_Annee *tabAnnees;
}T_Section;

#endif /* STRUCTURES_H_ */
