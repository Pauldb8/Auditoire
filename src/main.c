/*
 ============================================================================
 Name        : Auditoire
 Author      : Paul, Célien And Steeves
 Version     : 0.1
 Copyright   : Do not reproduce without the authors' authorization.
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/*Incusions des headers*/
#include "structures.h"
#include "operationsChoix.h"
#include "chargementSection.h"
#include "tools.h"
#include "defines.h"
#include "creerSection.h"

int main(void) {
	int choix;
	T_Section sectionChargee;
	setvbuf(stdout, NULL, _IONBF, 0); //Pour Eclipse

	effacerEcran();//Efface l'écran et affiche le titre du programme

	printf("Que voulez-vous faire ??\n\n");
	printf("\t1. Charger une section\n");
	printf("\t2. Creer une nouvelle section");
	printf("\n\nVotre choix : ");

	/*L'utilisateur doit faire un choix, 1 ou 2, mais pas d'autres choix possibles*/
	choix = getNumber(1,2);

	if(choix == 1)
    {
        sectionChargee = (T_Section) choisirSectionACharger(URL_SECTIONS);
        effacerEcran();
		administrationAnnees(&sectionChargee);
    }


    else if (choix == 2)
        sectionChargee = (T_Section) creerSection(URL_SECTIONS);


	//todo: add else
	printf("Fin correcte du programme\n");

	return EXIT_SUCCESS;
}
