/*
 * operationsEtudiants.h
 *
 *  Created on: 14 mai 2013
 *      Author: Paul
 */

#ifndef OPERATIONSETUDIANTS_H_
#define OPERATIONSETUDIANTS_H_

void administrationClasse(char*, char*, char*, T_Cours*, int);
void ajouterEtudiant(T_Classe *, int);
void sauvegarderClasse(T_Classe, char*, char*);
T_Classe chargerClasse(char*, char*);
void afficherClasse(T_Classe);
double calculerMoyenne(T_Etudiant, int);
int calculerNombreEchecs(T_Etudiant, int);
void modifierEtudiant(T_Classe *, T_Cours*, int);
void trierEtudiant(T_Classe *);
int fcomp(const void * a, const void * b);
int rechercherEtudiant(T_Classe a, char mat[]);
void modifierAdresse(T_Etudiant * etu);
void modifierCotes(T_Etudiant * etu, T_Cours*, int);
void supprimerEtudiant(T_Classe *);
void afficherClassement(T_Classe * a, char*, char*);
void afficherClassementConsole(T_Classe);
void afficherClassementTexte(T_Classe, char*, char*);



#endif /* OPERATIONSETUDIANTS_H_ */
