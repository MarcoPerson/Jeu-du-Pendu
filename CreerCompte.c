#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>

#include "CreerCompte.h"
#include "FonctionsUsuelles.h"

struct Joueur{
    char utilisateur[20];
    char motdepasse[20];
    int point;
};

long creerCompte(){
	/*Declaration et initialisation*/
    struct Joueur tabJoueur[100];
    FILE * fichier1;
	FILE * fichier2;
    int nbreJoueur = 0;
    int nbreSave = 0;
	char pseudo[20];
	char password[20];
	char confirmPassword[20];
	int pseudoExiste = 0;
	int positionJoueur = 0;
	int *PpositionJoueur;
	int verificationPassword;
	int verificationPseudo = 0;
	int recommencerCreation = 0;
	long choix = 1;

	PpositionJoueur = &positionJoueur;;

	/*Lecture des donnees existantes*/
	fichier1 = fopen("SaveN.bin", "ab+");
	if (fichier1 == NULL)
	{
	    printf("\n\nErreur d'ouverture du fichier SaveN\n");
		exit(1);
	}
	fscanf(fichier1, "%d", &nbreJoueur);
	fclose(fichier1);
	fichier2 = fopen("SaveJ.bin", "ab+");
	if(fichier2 == NULL){
        printf("\n\nErreur d'ouverture du fichier SaveJ.bin\n");
		exit(1);
	}
	fread(tabJoueur, sizeof(struct Joueur), nbreJoueur, fichier2);
	fclose(fichier2);

	/*Creation du compte*/
	while (choix == 1){
		printf("\nCreation du Compte\n");

		/*Verifier si le pseudo existe deja dans la base de donnees*/
		printf("\nEntrer votre Pseudo : ");
		lireChaine(pseudo, 20);
		verificationPseudo = verifPseudo(pseudo, tabJoueur, PpositionJoueur);
		if(verificationPseudo == 1){
			printf("\nUn compte porte deja ce nom.\nVeuillez choisir un autre Pseudo\n");
			recommencerCreation = 1;
		}
		if (recommencerCreation == 0)
		{
			/*Continuer si le pseudo n'existe pas*/
			printf("Entrer votre Mot de passe : ");
			MotDePasse(20, password);
			printf("Confirmer votre Mot de Passe : ");
			MotDePasse(20, confirmPassword);
			verificationPassword = strcmp(password, confirmPassword);
			if (verificationPassword == 0){
				printf("\n%s, vous avez ete enregistre avec succes\n", pseudo);

				/*Enregistrement des joueurs dans la tabJoueur*/
				strcpy(tabJoueur[nbreJoueur].utilisateur, pseudo);
				strcpy(tabJoueur[nbreJoueur].motdepasse, password);
				tabJoueur[nbreJoueur].point = 0;
				nbreJoueur++;
				nbreSave++;

				/*Sauvegarde des Joueurs*/
				fichier2 = fopen("SaveJ.bin", "wb+");
				if (fichier2 == NULL)
				{
					printf("\n\nErreur d'ouverture du fichier SaveJ.bin\n");
					exit(1);
				}
				fwrite(tabJoueur, sizeof(struct Joueur), nbreJoueur, fichier2);
				fclose(fichier2);

				/*Sauvegarde du nombre de Joueur*/
				fichier1 = fopen("SaveN.bin", "wb+");
				if (fichier1 == NULL)
				{
					printf("\n\nErreur d'ouverture du fichier SaveN.bin\n");
				}
				fprintf(fichier1, "%d", nbreJoueur);
				fclose(fichier1);
			}
			else {
				printf("\nMot de passe non confirme\n");
			}
			choix = retour();
		}
		else{
			choix = 0;
		}
	}
	printf("\n%d sauvegarde(s) enregistre(s)\n", nbreSave);
	return choix;
}
