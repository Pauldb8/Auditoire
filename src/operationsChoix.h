/*
 * operationsChoix.h
 *
 *  Created on: 11 mai 2013
 *      Author: Pauldb
 */

#ifndef OPERATIONSCHOIX_H_
#define OPERATIONSCHOIX_H_

void creerEtudiant(T_Classe *);
void administrationAnnees(T_Section *);
void choisirAnnee(T_Annee *);
void afficherMenuChoixAnnee(T_Section * tab);
void afficherMenuChoixClasse(T_Section, int);

#endif /* OPERATIONSCHOIX_H_ */

