/*
 * structures.h
 *
 *  Created on: 10 mai 2013
 *      Author: Paul, Célien And Steeves
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#define MAX_CHAR 51


typedef struct{
    char rue[MAX_CHAR];
    char ville[MAX_CHAR];
    int num;
    int cp;
}T_Adresse;

typedef struct
{
    char matricule[MAX_CHAR];
    char nom[MAX_CHAR];
    char prenom[MAX_CHAR];
    double tabCotes[5];
    double moyennePourcentage;
    T_Adresse adr;
}T_Etudiant;

typedef struct{
    char nomCours[MAX_CHAR];
    int ponderation;
}T_Cours;

typedef struct{
    char nomClasse[MAX_CHAR];
    int nbEtu;
    T_Etudiant * classe;
}T_Classe;

// Definition d'une annee/section (1TI)
typedef struct{
    char nomAnneeSection[MAX_CHAR];
    int nbClasses;
    char **nomClasse; // Tableau contenant le nom des classes. (1TM1)
    int nbCoursParEtudiant;
    T_Cours *tabCours;
    T_Classe *tabClasse; // Tableau de classe, exemple : 1TM1 (on ne sauvegardes pas ce champ)
}T_AnneeSection;


#endif /* STRUCTURES_H_ */
