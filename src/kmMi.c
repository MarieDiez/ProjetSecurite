#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
	
	int rep;
	bool finished = false;

	while(!finished){
		printf("%s\n", "1 - Km vers Miles");
		printf("%s\n", "2 - Miles vers Km");
		scanf("%d",&rep);
		if (rep == 1){
			finished = true;
			double km;
			printf("%s ", "Nombre de Km : ");
			scanf("%lf",&km);
			double mi = km * 0.62137;
			printf("%.2f Miles\n", mi);
		} else if (rep ==2){
			finished = true;
			double mi;
			printf("%s ", "Nombre de Miles : ");
			scanf("%lf",&mi);
			double km = mi / 0.62137;
			printf("%.2f Km\n", km);
		} else {
			printf("%s\n", "répondez correctement");
		}
	}


	return EXIT_SUCCESS;
}