/*
 ============================================================================
 Name        : Auditoire.c
 Author      : Paul, Célien And Steeves
 Version     : 0.1
 Copyright   : Do not reproduce without the authors' authorization.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "operationsChoix.h"
#include "chargementSection.h"
#include "tools.h"
#include "defines.h"

int main(void) {
	int choix, nbrAnnee;
	T_Section sectionChargee;
	setvbuf(stdout, NULL, _IONBF, 0); //Pour Eclipse
	effacerEcran();//Efface l'écran et affiche le titre du programme
	printf("Que voulez-vous faire ?\n");
	printf("\t1.Charger une section\n");
	printf("\t2.Créer une nouvelle section");
	printf("\n\nVotre choix : ");
	choix = getNumber(1,2);
	if(choix == 1)
		sectionChargee = (T_Section) choisirSectionACharger(URL_SECTIONS);
	//todo: add else
	printf("Fin correcte du programme");
	//T_Annee * tabAnnee; // Ecole (tabAnnneeSection)
    //afficherMenuGlobal(tabAnnee);
	return EXIT_SUCCESS;
}
