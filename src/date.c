#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(){

  	time_t now;
  	time(&now);
  	int jour, mois, annee;
  	int jour0, mois0,annee0;
  	int jourDiff, moisDiff, anneeDiff;

  	printf("%s ", "Entrée un jour :");
  	scanf("%d", &jour0);
  	printf("%s ", "Entrée un mois :");
  	scanf("%d", &mois0);
  	printf("%s ", "Entrée une année :");
  	scanf("%d", &annee0);
  	printf("\n%s : %d/%d/%d\n", "Date entrée",jour0,mois0,annee0);

	struct tm *local = localtime(&now);
	jour = local->tm_mday;
	mois = local->tm_mon + 1;
	annee = local->tm_year + 1900;
	printf("Date d'aujourd'hui : %02d/%02d/%d\n", jour, mois, annee);

	if(jour < jour0){
		if (mois == 3) {
			if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
				jour += 29;
			} else {
				jour += 28;
			}
		} else if (mois == 5 || mois == 7 || mois == 10 || mois == 12) {
			jour += 30;
        } else {
           jour += 31;
        }
        mois = mois - 1;
    }

    if (mois < mois0) {
        mois += 12;
        annee -= 1;
    }

	jourDiff = abs(jour - jour0);
	moisDiff = abs(mois - mois0);
	anneeDiff = abs(annee - annee0);

	printf("%s : %d jours %d mois %d ans\n","Temps d'écart", jourDiff, moisDiff, anneeDiff);
	return EXIT_SUCCESS;
}
