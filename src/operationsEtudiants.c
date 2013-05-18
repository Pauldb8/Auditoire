#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> //traitement des erreurs pour fopen
#include "structures.h"
#include "tools.h"
#include "defines.h"
#include "sauvegardeFichier.h"
#include "operationsEtudiants.h"

#define INCREMENTALLOC 3

extern int errno ;

void sauvegarderClasse(T_Classe classe, char *nomSection, char *nomAnnee){
	FILE *fichier;
	char* url;
	int nbEtu = classe.nbEtu;
	url = malloc(MAX_CHAR * sizeof(char));//malloc de l'url
	if(url == NULL)
        exit(0);

	//Génération de l'url
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES ,nomSection, nomAnnee, classe.nomClasse);
	if(DEBUG)
		printf("\n\nURL : %s\n\n", url);

	//Ouverture du fichier
	fichier = fopen(url, "wb+");
	if(fichier == NULL)
    {
		printf("Erreur lors de l'ouverture de %s\n", url);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
	}

	/*Enregistrement dans le fichier*/
	else
    {
		fwrite(&classe, sizeof(T_Classe), 1, fichier);
		fwrite(classe.eleves, nbEtu * sizeof(T_Etudiant), 1, fichier);
		fclose(fichier);
		printf("Fichier correctement enregistre !\n\n");
		system("PAUSE");
	}
}

/*
 * chargerClasse(url, nomClasse): Cette fonction reçoit une URL de fichier binaire
 * contenant toutes les informations d'une classe, elle les charge dans une strucutre
 * de type T_Classe et les renvoit.
 * @param : url du fichier binaire.
 * @param : nom de la classe que l'on crée
 * @return : un strucutre de type T_Classe remplie du fichier binaire.
 */
T_Classe chargerClasse(char *url, char* nomClasse){
	FILE *fichier = NULL;
	T_Classe returnClasse;
	T_Classe *returnClasseVide = NULL;

	fichier = fopen(url, "rb");
	if(fichier == NULL)
    {
		returnClasseVide = (T_Classe*) malloc(sizeof(T_Classe));

		//Si le fichier de chargement de classe n'existe pas
		//On crée une classe vide avec son nom et le nombre d'étudiant à 0.
		strcpy(returnClasseVide->nomClasse, nomClasse);
		returnClasseVide->nbEtu = 0;

		printf("La classe \"%s\" est vide, vous devrez la remplir.\n", nomClasse);
		return *returnClasseVide;
	}

	else
    {   //On lit d'abord la classe, comme cela on sait le nombre d'étudiants à mallocer.
		fread(&returnClasse, sizeof(T_Classe), 1, fichier);

		returnClasse.eleves = malloc(returnClasse.nbEtu * sizeof(T_Etudiant));
		if(returnClasse.eleves == NULL)
            exit(0);
		fread(returnClasse.eleves, returnClasse.nbEtu * sizeof(T_Etudiant), 1, fichier);

		printf("Classe %s correctement chargee : ", returnClasse.nomClasse);
		printf("il y a %d etudiants\n", returnClasse.nbEtu);
		return returnClasse;
	}
}

/*
 * afficherClasse(T_Classe): Cette fonction affiche tous les élèves ainsi que leurs
 * notes dans la console.
 * @param: La structure classe à afficher.
 */
void afficherClasse(T_Classe a)
{
    effacerEcran();
	int i;

	printf("*** Affichage de la classe %s *** \n\n", a.nomClasse);

	if(a.nbEtu == 0)
    {
        printf("\nAucun etudiant presents dans cette classe\n\n");
        system("Pause");
        effacerEcran();
    }

	for(i = 0; i < a.nbEtu; i++)
    {
        printf("*** Etudiant %d ***\n", i+1);
        printf("Matricule : %s\n", a.eleves[i].matricule);
		printf("Nom eleve : %s\n", a.eleves[i].nom);
		printf("Prenom : %s\n", a.eleves[i].prenom);
		printf("Moyenne : %2.1lf pourcents\n", a.eleves[i].moyennePourcentage);
		printf("Nombre d'echecs : %d\n", a.eleves[i].nbEchecs);
		printf("Adresse : Rue %s, numero %d, %d %s\n", a.eleves[i].rue, a.eleves[i].num, a.eleves[i].cp, a.eleves[i].ville);
		printf("\n");
	}

	system("pause");
	effacerEcran();
}


/**
 * Affiche un menu de choix des options possibles sur la classe.
 */
void administrationClasse(char* nomClasse, char* nomSection, char* nomAnnee, T_Cours *tabCours, int nbCours)
{
	int choix;
	char* url;
	T_Classe classe;
	strcpy(classe.nomClasse, nomClasse);
	/*On initialise le nombre d'étudiant à zero au début car on n'a pas encore lu la classe, qui est censée ne pas contenir d'étudiant pour le moment*/
	classe.nbEtu = 0;
	/*Malloc de départ*/
	classe.eleves = malloc(INCREMENTALLOC * sizeof(T_Etudiant));
	if(classe.eleves == NULL)
        exit(0);

	effacerEcran();

	/*Chargement du fichier de la classe SI existant*/
    url = malloc(MAX_CHAR * sizeof(char));
    if(url == NULL)
        exit(0);
	sprintf(url, "%s%s.%s.%s.bin", URL_CLASSES, nomSection, nomAnnee, nomClasse);

	/*Chargement de la classe*/
	classe = chargerClasse(url, nomClasse);

    do
    {
        printf("***Gestion d'une classe***\n\n");
        	printf("\tEtudiants:");
				printf("\n\t\t1. Ajouter un etudiant");
				printf("\n\t\t2. Modifier un etudiant");
				printf("\n\t\t3. Supprimer un etudiant");
			printf("\n\tClasse:");
				printf("\n\t\t4. Afficher la classe");
				printf("\n\t\t5. Afficher un classement des etudiants");
				printf("\n\t\t6. Sauvegarder la classe");
        printf("\n\n\t\t7. Retour\n\n");
        printf("Votre choix : ");
        choix = getNumber(1, 7);

        switch(choix)
        {
            case 1:
                ajouterEtudiant(&classe, nbCours);
                break;
            case 2 :
                modifierEtudiant(&classe, tabCours, nbCours);
                break;
            case 3 :
                supprimerEtudiant(&classe);
                break;
            case 4:
                afficherClasse(classe);
                break;
            case 5 :
                afficherClassement(&classe, nomSection, nomAnnee);
                break;
            case 6:
                sauvegarderClasse(classe, nomSection, nomAnnee);
                break;
        }

    }while(choix != 7);

}

void afficherClassement(T_Classe * a, char *nomSection, char *nomAnnee)
{
    effacerEcran();
    printf("*** Classement des eleves ***\n\n");
    printf("Que voulez vous faire ?\n\n");
    printf("\t1. Afficher le classement des eleves dans la console\n");
    printf("\t2. Generer un fichier texte contenant le classment des ces eleves\n\n");
    printf("Votre choix : ");

    int choix = getNumber(1, 2);

    if(choix == 1)
        afficherClassementConsole(*a);
    else if(choix == 2)
        afficherClassementTexte(*a, nomSection, nomAnnee);
}

void afficherClassementTexte(T_Classe a, char * nomSection, char * nomAnnee)
{
    FILE *fichier = NULL;
	char* url = NULL;
	url = malloc(MAX_CHAR * sizeof(char));//malloc de l'url
	if(url == NULL)
        exit(0);
	int i = 0;

	//Génération de l'url
	sprintf(url, "%s%s.%s.%s.classement.txt", URL_CLASSES, nomSection, nomAnnee, a.nomClasse);
	if(DEBUG)
		printf("\n\nURL : %s\n\n", url);

	//Ouverture du fichier en lecture seule.
	fichier = fopen(url, "w+");

	if(fichier != NULL)
    {
        fprintf(fichier, "Classement\t\tNom\t\t\tMoyenne\t\t\tNombre d'echecs\t\t\n\n");

        for(i = 0 ; i < a.nbEtu ; i++)
        {
            fprintf(fichier, "%d.\t\t|\t%s\t\t|\t%2.1lf\t\t|\t\t%d\n", i+1, a.eleves[i].nom, a.eleves[i].moyennePourcentage, a.eleves[i].nbEchecs);
        }

        fclose(fichier);

        printf("Fichier correctement enregidtrer sous %s\n\n", url);
        system("pause");
	}

	else
    {
        printf("Erreur lors de l'ouverture de %s\n", url);
		perror ("The following error occurred");
		printf( "Value of errno: %d\n", errno );
		exit(0);
    }


}

void afficherClassementConsole(T_Classe a)
{
    effacerEcran();
    trierEtudiant(&a);
    int i;

    printf("Classement\t\tNom\t\t\tMoyenne\t\t\tNombre d'echecs\t\t\n\n");

    for(i = 0 ; i < a.nbEtu ; i++)
    {
        printf("%d.\t\t|\t%s\t\t|\t%2.1lf\t\t|\t\t%d\n", i+1, a.eleves[i].nom, a.eleves[i].moyennePourcentage, a.eleves[i].nbEchecs);
    }

    printf("\n");
    system("pause");
    effacerEcran();
}

void supprimerEtudiant(T_Classe *a)
{
    int i = 0;
    char mat[MAX_CHAR];
    char sur;

    effacerEcran();
    printf("\n");
    printf("*** Menu de suppresion d'un etudiant *** \n\n");

    printf("Matricule de l'etudiant a supprimer : ");
    fflush(stdin); 
    scanf("%s", mat);

    /*Resultat recherche correspond à l'indice de l'étudiant, si celui-ci existe.*/
    int indiceEtu = rechercherEtudiant((*a), mat);

    if(indiceEtu == -1)
    {
        printf("Ce Matricule n'existe pas. ");
        system("pause");
    }

    else
    {
        printf("Etes-vous sur de vouloir supprimer %s (O/N) : ", a->eleves[indiceEtu].nom);
        fflush(stdin);
        scanf("%c", &sur);
        if((sur == 'O') || (sur == 'o'))
        {
            for(i = indiceEtu ; i < (*a).nbEtu-1 ; i++){
                a->eleves[indiceEtu] = a->eleves[indiceEtu + 1];
            }
            a -> nbEtu--;
            a->eleves = realloc(a->eleves, sizeof(T_Etudiant) * a->nbEtu); //On diminue l'espace pris en m�moire.
            printf("OK ! ");
            system("pause");
            system("cls");
        }
        else
        {
            printf("\n Annulation ! ");
            system("pause");
        }
    }
}

int fcomp(const void * a, const void * b)
{
    const T_Etudiant *ia = (T_Etudiant *) a;
    const T_Etudiant *ib = (T_Etudiant*) b;

    if( (ia->moyennePourcentage) - (ib->moyennePourcentage) > 0)
        return -1;

    else if( (ia->moyennePourcentage) - (ib->moyennePourcentage) == 0)
        return 0;

    else
        return 1;
}

void trierEtudiant(T_Classe * a)
{
    qsort(a->eleves, a->nbEtu, sizeof(T_Etudiant), fcomp);
}

void modifierEtudiant(T_Classe * a, T_Cours *tabCours, int nbCours)
{
    char mat[MAX_CHAR];
    int indiceEtu;
    int choix = 0;

    effacerEcran();
    printf("*** Modification d'un etudiant *** \n\n");
   do{
		printf("Matricule de l'etudiant a modifier : ");
		scanf("%s", mat);
		trierEtudiant(a);

		indiceEtu = rechercherEtudiant(*a, mat);
		if(indiceEtu == -1)
		{
			printf("Ce matricule n'existe pas.\n");
			system("pause");
		}
		effacerEcran();
   }while(indiceEtu == -1);

    printf("Que voulez vous modifier ?\n");
    do
    {
        printf("\t1. Les cotes de l'etudiant\n");
        printf("\t2. L'adresse de l'etudiant\n");
        printf("\t3. Retour\n");
        printf("Votre choix : ");
        choix = getNumber(1, 3);

        if(choix == 1)
            modifierCotes(&a->eleves[indiceEtu], tabCours, nbCours);
        if(choix == 2)
            modifierAdresse(&a->eleves[indiceEtu]);

    }while(choix != 3);

    effacerEcran();


}

void modifierCotes(T_Etudiant * etu, T_Cours *tabCours, int nbCours)
{
	int i = 0;
	
	/*Malloc de départ, sans quoi le realloc ne fonctionne pas*/
	etu->tabCotes = malloc(INCREMENTALLOC * sizeof(T_Cours));

	//Allocation du tableau de cotes:
	etu->tabCotes = realloc(etu->tabCotes, sizeof(T_Cours) * nbCours);
	effacerEcran();
    for(i = 0; i < nbCours; i++){
    	printf("Note en %s : ", tabCours[i].nomCours);
    	scanf("%lf", &(etu->tabCotes[i]) );
    }
    etu->moyennePourcentage = calculerMoyenne(*etu, nbCours);
    etu->nbEchecs = calculerNombreEchecs(*etu, nbCours);
    printf("Cotes correctement modifiees\n\n");
    system("pause");

}

void modifierAdresse(T_Etudiant * etu)
{
    effacerEcran();
    printf("***** Modification de l'adresse de l'etudiant au matricule : %s *****\n\n", etu->matricule);
    printf("Nouvelle ville \t: ");
    fflush(stdin);
    gets(etu->ville);
    printf("Nouvelle rue \t: ");
    fflush(stdin);
    gets(etu->rue);
    printf("Nouveau numero \t: ");
    scanf("%d", &(etu->num) );
    printf("Nouveau CP \t: ");
    scanf("%d", &(etu->cp) ) ;
    printf("\n");
    system("pause");

}

/*
PRE  : Auditoire et char[] correctement initialisée.
POST : Si etudiant retrouvé, on revoie son indice, sinon, on renvoie -1.
*/
int rechercherEtudiant(T_Classe a, char mat[])
{
    int i, indiceEtu = -1;

    for(i = 0 ; i < a.nbEtu ; i++)
    {
        if(strcmp(a.eleves[i].matricule,mat) == 0)
            indiceEtu = i;
    }

    return indiceEtu;

}

void ajouterEtudiant(T_Classe * a, int nbCours)
{
    T_Etudiant etu;
    char recommencer = 0;
    int i;
    effacerEcran();

    printf("*** Menu d'ajout d'un etudiant dans la classe %s ***\n\n", a->nomClasse);

    do{
        printf("Matricule : ");
        fflush(stdin);
        gets(etu.matricule);
        printf("Nom : ");
        fflush(stdin);
        gets(etu.nom);
        printf("Prenom : ");
        fflush(stdin);
        gets(etu.prenom);
        printf("Numero de rue : ");
        fflush(stdin);
        scanf("%d", &etu.num);
        printf("Rue : ");
        fflush(stdin);
        gets(etu.rue);
        printf("Code Postal (valide, donc entre 1000 et 9999) : ");
        fflush(stdin);
        scanf("%d", &etu.cp);
        printf("Ville : ");
        fflush(stdin);
        gets(etu.ville);

        etu.tabCotes = (double*) malloc(sizeof(double) * nbCours);
        /*Mise à zero des cotes */
        for (i = 0 ; i < nbCours ; i++)
            etu.tabCotes[i] = 0;

        etu.moyennePourcentage = calculerMoyenne(etu, nbCours);
        etu.nbEchecs = calculerNombreEchecs(etu, nbCours);

        a->eleves = realloc(a->eleves,(a->nbEtu + INCREMENTALLOC) * sizeof(T_Etudiant));

        a->eleves[a->nbEtu] = etu;
        a->nbEtu ++;

        printf("Ajouter encore un etudiant ? (o/n) ");
        fflush(stdin);
        scanf("%c", &recommencer);

        }while(recommencer == 'o' || recommencer == 'O');

        effacerEcran();

}

/*Ne tiens (pas encore) compte de la pondération des cours.*/
double calculerMoyenne(T_Etudiant etu, int nbCours)
{
    int i;
    double restTemp = 0, moy, moyPourcent;

    for(i = 0 ; i < nbCours ; i++)
        restTemp += etu.tabCotes[i];

    moy = restTemp/nbCours;

    moyPourcent = (moy * 100) / 20;

    return moyPourcent;

}

int calculerNombreEchecs(T_Etudiant etu, int nbCours)
{
    int i, nbr = 0;

    for(i = 0 ; i < nbCours; i++)
    {
        if(etu.tabCotes[i] < 10)
            nbr++;
    }

    return nbr;
}
