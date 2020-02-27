#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int main(){

	srand(time(0));
	char piece[4];
	int choixUser;
	bool continuer = true;
	char c[1];
	int argent = 100;
	printf("Pile ou face ! (q/Q pour quitter)\n");
	int mise = 0;

	while(continuer){
		printf("%s : %d€\n", "Vous avez",argent);
		printf("%s : ","Quelle est votre mise ");
		scanf("%d",&mise);
		if (mise > argent){
			mise = argent;
			printf("%s : %d€\n", "Votre mise est de",mise);
		}

		printf("%s ", "Pile ou face ? (p/f)");
		scanf("%s",&piece);
		int facePiece = rand()%2;

		if (strcmp(piece,"face") == 0 || strcmp(piece,"f") == 0 || strcmp(piece,"F") == 0){
			choixUser = 0;
		} else if (strcmp(piece,"pile") == 0 || strcmp(piece,"p") == 0 || strcmp(piece,"P") == 0){
			choixUser = 1;
		} else if (strcmp(piece,"q") == 0 || strcmp(piece,"Q") == 0){
			return EXIT_SUCCESS;
		} else {
			printf("%s\n", "Erreur d'écriture");	
		}

		if (facePiece == choixUser ){
			printf("%s\n\n", "Gagner !");
			argent = argent + mise;
			printf("%s : %d€\n","Vous gagner votre mise, vous avez",argent);
		} else if (facePiece != choixUser){
			printf("%s\n\n", "Perdu !");
			argent = argent - mise;
			if (argent <= 0){
				continuer = false;
			} else {
				printf("%s : %d€\n","Vous perdez votre mise, il vous reste",argent);
			}
			
		}
	}
	if (argent <= 0){
		printf("%s\n", "Vous n'avez plus d'argent !");
	}
	return EXIT_SUCCESS;
}