#include <stdio.h>
#include <stdlib.h>

#include "MeilleursScores.h"

struct Joueur{
    char utilisateur[20];
    char motdepasse[20];
    int point;
};

long meilleursScores(){
	printf("\nMeilleurs Scores\n");

	/*Declaration et Initialisation*/
	struct Joueur tabJoueur[100];
	struct Joueur temp;
    FILE * fichier1;
	FILE * fichier2;
    int nbreJoueur = 0;
    int max = 0;

	/*Lecture des donnees existantes*/
	fichier1 = fopen("SaveN.bin", "ab+");
	if (fichier1 == NULL)
	{
	    printf("\n\nErreur d'ouverture du fichier SaveN.bin\n");
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
    if(nbreJoueur == 0){
        printf("\nAucune donnee enregistree pour l'instant\n ");
    }
	/*Tri de tabJoueur par ordre decroissant*/
	for (int i = 0; i < nbreJoueur - 1; ++i)
	{
		max = i;
		for (int u = i+1; u < nbreJoueur; ++u)
		{
			if(tabJoueur[max].point < tabJoueur[u].point){
				max = u;
			}
		}
		if (max != i)
		{
			strcpy(temp.utilisateur, tabJoueur[i].utilisateur);
			strcpy(temp.motdepasse, tabJoueur[i].motdepasse);
			temp.point = tabJoueur[i].point;
			strcpy(tabJoueur[i].utilisateur, tabJoueur[max].utilisateur);
			strcpy(tabJoueur[i].motdepasse, tabJoueur[max].motdepasse);
			tabJoueur[i].point = tabJoueur[max].point;
			strcpy(tabJoueur[max].utilisateur, temp.utilisateur);
			strcpy(tabJoueur[max].utilisateur, temp.motdepasse);
			tabJoueur[max].point = temp.point;
		}
	}

	/*Enregistrement du nouveau tableau*/
	fichier2 = fopen("SaveJ.bin", "wb+");
	if(fichier2 == NULL){
        printf("\n\nErreur d'ouverture du fichier SaveJ.bin\n");
		exit(1);
	}
	fwrite(tabJoueur, sizeof(struct Joueur), nbreJoueur, fichier2);
	fclose(fichier2);

	/*Affichage des 5 premiers meilleurs scores*/
	if (nbreJoueur >= 5)
	{
		for (int i = 0; i < 5; ++i)
		{
			printf("\n%d-\t%3d\t%s", i+1, tabJoueur[i].point, tabJoueur[i].utilisateur);
		}
		printf("\n");
	}
	else{
		for (int i = 0; i < nbreJoueur; ++i)
		{
			printf("\n%d-\t%3d\t%s", i+1, tabJoueur[i].point, tabJoueur[i].utilisateur);
		}
		printf("\n");
	}
	return 0;
}
