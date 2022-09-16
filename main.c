#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>

#include "FonctionsUsuelles.h"
#include "Jouer.h"
#include "CreerCompte.h"
#include "MeilleursScores.h"
#include "Instructions.h"
#include "Quitter.h"

long menu();

struct Joueur{
    char utilisateur[20];
    char motdepasse[20];
    int point;
};

int verifPseudo(char *pseudo, struct Joueur tabJoueur[100], int *position);
int verifPassword(char *password, struct Joueur tabJoueur[100], int *position);

long menu(){
	long choix = 0;
	printf("\nMenu du Jeu\n");
	printf("\n1- Jouer\n");
	printf("2- Creer un compte\n");
	printf("3- Meilleurs Scores\n");
	printf("4- Instructions\n");
	printf("5- Quitter\n");
	printf("\nVotre Choix : ");
	choix = lireEntier();
	return choix;
}

int main(int argc, char const *argv[])
{
    setlocale(LC_CTYPE,"");
	long choixMenu = 0;
	long choixRetour = 0;
	presentation();
	while(choixRetour == 0){
		choixMenu = menu();
		switch (choixMenu){
			case 1:
				choixRetour = Jouer();
				break;
			case 2:
				choixRetour = creerCompte();
				break;
			case 3:
				choixRetour = meilleursScores();
				break;
			case 4:
				choixRetour = instructions();
				break;
			case 5:
				choixRetour = quitter();
				break;
			default:
				printf("\nEntrer une valeur compris entre 1 et 5\n");
				break;
		}
	}
	return 0;
}
