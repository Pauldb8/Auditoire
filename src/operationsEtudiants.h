/*
 * operationsEtudiants.h
 *
 *  Created on: 14 mai 2013
 *      Author: Paul
 */

#ifndef OPERATIONSETUDIANTS_H_
#define OPERATIONSETUDIANTS_H_

void administrationClasse(char*, char*, char*);
void ajouterEtudiant(T_Classe *);
void sauvegarderClasse(T_Classe, char*, char*);
T_Classe chargerClasse(char*, char*);
void afficherClasse(T_Classe);

#endif /* OPERATIONSETUDIANTS_H_ */
