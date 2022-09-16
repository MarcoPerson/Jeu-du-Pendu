#include <stdio.h>
#include <stdlib.h>

#include "FonctionsUsuelles.h"

void presentation(){
	printf("\nBienvenue dans le Jeu de Lettre\n");
	printf("Consulter l'instructions pour voir les regles du Jeu\n");
}

void viderBuffer(){
	int c = 0;
	while(c != '\n' && c != EOF){
		c = getchar();
	}
}

int lireChaine(char *chaine, int nombre){
	char *position = NULL;
	if(fgets(chaine, nombre, stdin) != NULL){
		if((position = strchr(chaine, '\n')) != NULL){
			*position = '\0';
		}
		else{
			viderBuffer();
		}
		return 1;
	}
	else{
		viderBuffer();
		return 0;
	}
}

long lireEntier(){
	char entier[3];
	if (lireChaine(entier, 3))
	{
		return strtol(entier, NULL, 10);
	}
	else{
		return 0;
	}
}

long retour(){
	long choix = 2;
	while(choix != 1 && choix != 0){
        printf("\nAppuyer sur : \n");
        printf("0- pour Retouner au Menu\n");
        printf("1- pour Continuer\n");
        printf("\nVotre Choix : ");
        choix = lireEntier();
	}
	return choix;
}

void MotDePasse(int nombre, char * password){
	char ch;
	for (int i = 0; i < nombre; ++i)
	{
		ch = getch();
		*(password + i) = ch;
		if (ch == '\r')
		{
		    *(password + i) = '\0';
			break;
		}
		ch = '*';
		printf("%c", ch);
	}
	printf("\n");
}

