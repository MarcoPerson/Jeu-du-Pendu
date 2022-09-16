#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>

#include "Jouer.h"
#include "FonctionsUsuelles.h"

struct Joueur{
    char utilisateur[20];
    char motdepasse[20];
    int point;
};

int verifPseudo(char *pseudo, struct Joueur tabJoueur[100], int *position);
int verifPassword(char *password, struct Joueur tabJoueur[100], int *position);

void choixMot(char * mot){
	FILE * fichier;
	int nbreAlea = 1;
	srand(time(NULL));
	nbreAlea = (rand() % 399) + 1;
	fichier = fopen("SaveM.bin", "r");
	if(fichier == NULL){
		printf("\nErreur d'ouverture l'hors du fichier\n");
		exit(1);
	}
	else{
		for (int i = 0; i < nbreAlea; ++i)
		{
			fgets(mot, 15, fichier);
		}
		*(mot + strlen(mot) - 1) = '\0';
	}
	fclose(fichier);
}

void masquerMot(char * mot, char * masqueMot){
	int i = 0;
	int nbreLettre = strlen(mot);
	for (i = 0; i < nbreLettre; ++i)
	{
		*(masqueMot + i) = '*';
	}
	*(masqueMot + i) = '\0';
}

void remplacerLettre(char lettre, char * mot, char * masqueMot, char *motFausse, int * chance){
	int verif = 0;
	char *position = NULL;
	for (int i = 0; i < strlen(mot); ++i)
	{
	    lettre = toupper(lettre);
	    if(lettre == *(masqueMot + i)){
            verif = 2;
	    }
		else if(lettre == *(mot + i))
		{
			*(masqueMot + i) = lettre;
			verif = 1;
		}
	}
	if (verif == 1){
		printf("Lettre trouvee !!!!\n");
		printf("Vous avez toujours %d chance(s)\n", *(chance));
	}
	else if(verif == 2){
        printf("Vous avez deja trouve cette lettre\n");
        printf("Vous avez toujours %d chance(s)\n", *(chance));
	}
	else{
		if((position = strchr(motFausse, lettre)) != NULL){
            verif = 3;
		}

		if (verif == 3)
		{
			printf("Vous avez deja fausse cette lettre\n");
			*(chance) = *(chance) - 2;
			if (*(chance) < 0)
			{
				*(chance) = 0;
			}
			printf("Il vous reste %d chance(s)\n", *(chance));
		}
		else{
			*(motFausse + strlen(motFausse)) = lettre;
			printf("Lettre erronee !!!!\n");
			*(chance) = *(chance) - 1;
			printf("Il vous reste %d chance(s)\n", *(chance));
		}
	}
}

int verifPseudo(char *pseudo, struct Joueur tabJoueur[100], int *position){
    int nbreJoueur = 0;
    int verif = 0;
    FILE * fichier1;
    FILE * fichier2;

    /*Lecture des Joueurs present*/
	fichier1 = fopen("SaveN.bin", "ab+");
	if (fichier1 == NULL)
	{
	    printf("\n\nErreur d'ouverture du fichier SaveN.bin\n");
		exit(1);
	};
	fscanf(fichier1, "%d", &nbreJoueur);
	fclose(fichier1);
	fichier2 = fopen("SaveJ.bin", "ab+");
	if(fichier2 == NULL){
        printf("\n\nErreur d'ouverture du fichier SaveJ.bin\n");
		exit(1);
	}
	fread(tabJoueur, sizeof(struct Joueur), nbreJoueur, fichier2);
	fclose(fichier2);

	for(int i = 0; i < nbreJoueur; i++){
        if(!strcmp(pseudo, tabJoueur[i].utilisateur)){
            verif = 1;
            *(position) = i;
            break;
        }
	}
	return verif;
}

int verifPassword(char *password, struct Joueur tabJoueur[100], int *position){
    int nbreJoueur = 0;
    int verif = 0;
    FILE * fichier1;
    FILE * fichier2;

    /*Lecture des Joueurs present*/
	fichier1 = fopen("SaveN.bin", "ab+");
	if (fichier1 == NULL)
	{
	    printf("\n\nErreur d'ouverture du fichier SaveN.bin\n");
		exit(1);
	};
	fscanf(fichier1, "%d", &nbreJoueur);
	fclose(fichier1);
	fichier2 = fopen("SaveJ.bin", "ab+");
	if(fichier2 == NULL){
        printf("\n\nErreur d'ouverture du fichier SaveJ.bin\n");
		exit(1);
	}
	fread(tabJoueur, sizeof(struct Joueur), nbreJoueur, fichier2);
	fclose(fichier2);

    if(!strcmp(password, tabJoueur[*(position)].motdepasse)){
        verif = 1;
    }
	return verif;
}

long Jouer(){
    /*Declaration*/
    FILE * fichier2;
    FILE * fichier1;
    struct Joueur tabJoueur[100];
    int nbreJoueur = 0;
	char pseudo[20];
	char password[20];
	char mot[15] = "", masqueMot[15] = "", motFausse[15] = "", lettre = 0;
	long choix = 1;
	int motTrouve = 1;
	int chance;
	int *Pchance;
	int point = 0;
	int pseudoExiste = 0;
	int passwordExiste = 0;
	int positionJoueur = 0;
	int *PpositionJoueur;

	/*Initialisation*/
	Pchance = &chance;
	PpositionJoueur = &positionJoueur;

	/*Lecture des Joueurs present*/
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

	/*Debut du Jeu*/
	printf("\nConnectez-vous\n");
	printf("\nPseudo : ");
	lireChaine(pseudo, 20);

    /*Verification de l'existence du Pseudo*/
    pseudoExiste = verifPseudo(pseudo, tabJoueur, PpositionJoueur);
    if(pseudoExiste == 1){
        do{
            printf("Mot de passe : ");
            MotDePasse(20, password);
            passwordExiste = verifPassword(password, tabJoueur, PpositionJoueur);
        }while(passwordExiste != 1);
        point = tabJoueur[positionJoueur].point;
        printf("\nVous avez un score de %d point(s)\n", point);
        while(choix){
            choixMot(mot);
            masquerMot(mot, masqueMot);
            chance = 10;
            printf("\nVoici le mot masque : %s\nElle est compose de %ld lettres\n", masqueMot, strlen(mot));
            printf("\nVous avez %d chances pour le trouver\n", chance);
            while (motTrouve && chance){
                printf("\nEntrer une lettre : ");
                fflush(stdin);
                scanf("%c", &lettre);
                fflush(stdin);
                remplacerLettre(lettre, mot, masqueMot, motFausse, Pchance);
                printf("%s", motFausse);
                printf("\nLe nouveau mot est %s\n", masqueMot);
                motTrouve = strcmp(mot, masqueMot);
            }
            if (chance){
                printf("\n\nFelicitations vous avez trouve le mot \n\n");
                point += chance;
                printf("\nVous avez maintenant %d point(s)\n", point);
                tabJoueur[positionJoueur].point = point;
                /*Sauvegarde des Joueurs*/
                fichier2 = fopen("SaveJ.bin", "wb+");
                if (fichier2 == NULL)
                {
                    printf("\n\nErreur d'ouverture du fichier Save.bin\n");
                    exit(1);
                }
                fwrite(tabJoueur, sizeof(struct Joueur), nbreJoueur, fichier2);
                fclose(fichier2);
            }
            else{
                printf("\n\nVous avez perdu\n\n");
                printf("Le mot etait %s\n", mot);
            }
            motTrouve = 1;
            for(int i = 0; i < 15; i++){
                motFausse[i] = '\0';
            }
            choix = retour();
        }
    }
    else{
            printf("\nVous n'avez pas de compte");
            printf("\nVeuiler creer un compte au Menu Principale\n");
            choix = 0;;
        }
	return 0;
}
