#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int incrementeCptInCircle(int cpt, double x, double y){
	if (x*x + y*y <= 1)
		cpt++;
	return cpt;
}

int main(){

	srand(time(0));
	double x;
	double y;
	int cpt = 0;
	int n;

	printf("%s\n", "Calcule de pi par l'approximation de monte-carlo : ");
	printf("%s\n", "Nombre de fléchette : ");
	scanf("%d", &n);
	
	for (int i=0; i<n; i++){
		x =  rand()/(double)RAND_MAX;
		y =  rand()/(double)RAND_MAX;

		cpt = incrementeCptInCircle(cpt,x,y);

	}

	printf("%s %.7f\n", "pi = ",((double)cpt*4)/n);
	

	return EXIT_SUCCESS;
} 