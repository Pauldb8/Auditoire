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

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0); //Pour Eclipse
    T_AnneeSection * tabAnneeSection; // Ecole (tabAnnneeSection)
    afficherMenuGlobal(tabAnneeSection);
	return EXIT_SUCCESS;
}
