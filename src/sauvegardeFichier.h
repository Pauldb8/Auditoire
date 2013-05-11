/*
 * sauvegardeFichier.h
 *
 *  Created on: 10 mai 2013
 *      Author: Pauldb
 */

#ifndef SAUVEGARDEFICHIER_H_
#define SAUVEGARDEFICHIER_H_
#include "structures.h"

void sauverFichierParametrage(T_Annee*, int);
int chargerFichierParametrage(char*, T_Annee*);
int recupererNombreAnnneeSection();

#endif /* SAUVEGARDEFICHIER_H_ */
