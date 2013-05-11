/*
 * tools.c
 *
 *  Created on: 11 mai 2013
 *      Author: Pauldb
 */

int getNumber(int min, int max){
	int number;
	do{
		scanf("%d", &number);
	}while((number > max) || (number < min));
	return number;
}

/*
 * @effacerEcran: Cette fonction efface l'écran et réaffiche le titre principal.
 * @param: aucun.
 * @return: aucun.
 */
void effacerEcran(){
	system("CLS");
	printf("***BIENVENUE AU PROGRAMME D'ADMINISTRATION DE L'EPHEC***\n");
}
