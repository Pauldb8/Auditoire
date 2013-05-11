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

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0); //Pour Eclipse
	T_Annee * tabAnnee; // Ecole (tabAnnneeSection)
    afficherMenuGlobal(tabAnnee);
	return EXIT_SUCCESS;
}
