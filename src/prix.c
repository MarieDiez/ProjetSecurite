#include <stdlib.h>
#include <stdio.h>

int main(){
	double prix;
	double reduc;

	printf("%s ", "Prix :");
	scanf("%lf",&prix);

	printf("%s ", "Pourcentage de réduction :");
	scanf("%lf",&reduc);

	printf("%s = %.2f€\n","Nouveau prix",prix-prix*(reduc/100));

	return EXIT_SUCCESS;
}