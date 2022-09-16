#include <stdio.h>
#include <stdlib.h>

#include "Instructions.h"

long instructions(){
	int choix;
	printf("\nInstructions\n");
	printf("\n\nCe jeu est connu sous le nom du Jeu du Pendu");
	printf("\n\n\tDescription du Jeu\n");
	printf("\nLe programme choisira un mot et votre objectif");
	printf("\nsera de le deviner le plus rapidement possible");
	printf("\n\n\tEtapes pour Jouer\n");
	printf("\nPour jouer a ce jeu, vous devez imperativement");
	printf("\navoir creer un compte");
	printf("\n\n\tCreation d'un compte\n");
	printf("\nPour creer un compte vous devez aller dans la ");
	printf("\nrubrique 2 du Menu du Jeu et suivre les instructions");
	printf("\nNB : Le Pseudo et le Mot de passe doivent être ");
	printf("\ninferieur a 20 caracteres");
	printf("\n\n\tJouer\n");
	printf("\nPour jouer, aller dans la rubrique 1 du Menu de ");
	printf("\nJeu et entrer vos donnees.");
	printf("\nVous debutez le jeu avec 0 point et vous avez 10 ");
	printf("\nchances pour deviner le mot choisi par le programme.");
	printf("\nLe nombre de chances qui reste sera considere ");
	printf("\ncomme le point gagne l'hors de cette partie.");
	printf("\nAu debut de chaque partie, le nombre de points totals ");
	printf("\ngagnes vous sera affiche.");
	printf("\nSi vous faussez une lettre deja faussee, le nombre");
	printf("\nde chances diminuera de deux et si vous rentrez une ");
	printf("\nlettre deja trouve, aucune chance ne sera enlevee");
	printf("\n\n\tMeilleurs Scores\n");
	printf("\nRubrique 3 du Jeu.");
	printf("\nAffiche les 5 personnes ayant gagnes le plus de points");
	printf("\n\nNB :   1- En Saisissant votre mot de passe, vous ne ");
	printf("\n          pouvez plus l'effacer. Soyer donc attentif a ");
	printf("\n          ce que vous saisissez !!!!!");
	printf("\n       2- L'Hors de la question du choix du Retour au ");
	printf("\n          Menu Principal ou non, si vous entrer une lettre");
	printf("\n          de l'alphabet, elle sera consideree comme 0.\n");
	printf("\nMerci\n");
	printf("\nAuteur : Marco Person");
	printf("\nSociete : Ispace");
	printf("\nMail : Marcoperson2000@gmail.com\n");
	choix = 0;
	return choix;
}
