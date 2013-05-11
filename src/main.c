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
#include "tools.h"
#define URL_SECTIONS "src/Sauvegardes" //Où chercher les dossiers de Sections

int main(void) {
	int choix;
	setvbuf(stdout, NULL, _IONBF, 0); //Pour Eclipse
	effacerEcran();//Efface l'écran et affiche le titre du programme
	printf("Que voulez-vous faire ?\n");
	printf("\t1.Charger une section\n");
	printf("\t2.Créer une nouvelle section");
	printf("\n\nVotre choix : ");
	choix = getNumber(1,2);
	if(choix == 1)
		choisirSectionACharger(URL_SECTIONS);
	//todo: add else
	T_Annee * tabAnnee; // Ecole (tabAnnneeSection)
    afficherMenuGlobal(tabAnnee);
	return EXIT_SUCCESS;
}
